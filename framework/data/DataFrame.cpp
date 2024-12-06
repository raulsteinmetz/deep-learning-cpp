#include "DataFrame.h"
#include "DataFrameIterator.h"
#include <algorithm>
#include <stdexcept>

void DataFrame::set_columns(const std::vector<std::string>& names) {
    column_names = names;
}

void DataFrame::append_row(const std::vector<long double>& row) {
    if (!column_names.empty() && row.size() != column_names.size()) {
        throw std::invalid_argument("Row size does not match column count");
    }
    data.push_back(row);
}

const std::vector<std::string>& DataFrame::get_columns() const {
    return column_names;
}

const std::vector<std::vector<long double>>& DataFrame::get_data() const {
    return data;
}

size_t DataFrame::row_count() const {
    return data.size();
}

size_t DataFrame::column_count() const {
    return column_names.size();
}

std::unique_ptr<DataFrame> DataFrame::dataframe_from_column(const std::string& column) const {
    auto it = std::find(column_names.begin(), column_names.end(), column);
    if (it == column_names.end()) {
        throw std::invalid_argument("Column '" + column + "' does not exist.");
    }

    size_t index = std::distance(column_names.begin(), it);

    auto result = std::make_unique<DataFrame>();
    result->set_columns({column});

    for (const auto& row : data) {
        result->append_row({row[index]});
    }

    return result;
}

void DataFrame::drop_columns(const std::vector<std::string>& columns) {
    std::vector<size_t> indices;
    for (const auto& col_name : columns) {
        auto it = std::find(column_names.begin(), column_names.end(), col_name);
        if (it == column_names.end()) {
            throw std::invalid_argument("Column '" + col_name + "' does not exist.");
        }
        indices.push_back(std::distance(column_names.begin(), it));
    }

    std::sort(indices.rbegin(), indices.rend());

    for (const auto& index : indices) {
        column_names.erase(column_names.begin() + index);
    }

    for (auto& row : data) {
        for (const auto& index : indices) {
            row.erase(row.begin() + index);
        }
    }
}

std::unique_ptr<Iterator> DataFrame::create_iterator() const {
    return std::make_unique<DataFrameIterator>(*this);
}
