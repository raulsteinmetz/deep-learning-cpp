#include "DataFrameUtils.h"
#include "CSVDataFrameFactory.h"
#include "JsonDataFrameFactory.h"
#include <stdexcept>

DataFrame DataFrameUtils::df_from_csv(const std::string& f_path) {
    CSVDataFrameFactory csvFactory;
    return csvFactory.create_dataframe(f_path);
}

DataFrame DataFrameUtils::df_from_json(const std::string& f_path) {
    JsonDataFrameFactory jsonFactory;
    return jsonFactory.create_dataframe(f_path);
}

std::tuple<DataFrame, DataFrame, DataFrame, DataFrame>
DataFrameUtils::train_test_split(const DataFrame& data, const DataFrame& target, float test_ratio) {
    if (test_ratio < 0.0f || test_ratio > 1.0f) {
        throw std::invalid_argument("test_ratio must be between 0 and 1.");
    }

    size_t total_rows = data.row_count();
    size_t test_size = static_cast<size_t>(total_rows * test_ratio);
    size_t train_size = total_rows - test_size;

    std::vector<size_t> indices(total_rows);
    for (size_t i = 0; i < total_rows; ++i) {
        indices[i] = i;
    }

    std::srand(static_cast<unsigned>(time(0)));
    std::random_shuffle(indices.begin(), indices.end());

    DataFrame train_data, test_data, train_target, test_target;
    train_data.set_columns(data.get_columns());
    test_data.set_columns(data.get_columns());
    train_target.set_columns(target.get_columns());
    test_target.set_columns(target.get_columns());

    for (size_t i = 0; i < total_rows; ++i) {
        if (i < train_size) {
            train_data.append_row(data.get_data()[indices[i]]);
            train_target.append_row(target.get_data()[indices[i]]);
        } else {
            test_data.append_row(data.get_data()[indices[i]]);
            test_target.append_row(target.get_data()[indices[i]]);
        }
    }

    return {train_data, test_data, train_target, test_target};
}
