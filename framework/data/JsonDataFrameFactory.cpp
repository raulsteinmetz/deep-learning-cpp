#include "JsonDataFrameFactory.h"
#include "DataFrame.h"
#include <iostream>
#include <nlohmann/json.hpp>

DataFrame JsonDataFrameFactory::create_dataframe(const std::string& f_path) const {
    std::ifstream file(f_path);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + f_path);
    }

    nlohmann::json json_data;
    try {
        file >> json_data;
    } catch (const std::exception& e) {
        throw std::runtime_error("Error parsing JSON: " + std::string(e.what()));
    }

    if (!json_data.is_array()) {
        throw std::invalid_argument("JSON must be an array of objects");
    }

    DataFrame df;

    bool is_header = true;
    std::vector<std::string> column_order;

    for (const auto& row : json_data) {
        if (!row.is_object()) {
            throw std::invalid_argument("JSON array must contain objects");
        }

        if (is_header) {
            for (const auto& [key, value] : row.items()) {
                column_order.push_back(key);
            }
            df.set_columns(column_order);
            is_header = false;
        }

        std::vector<long double> row_data;
        for (const auto& key : column_order) {
            try {
                row_data.push_back(row.at(key).get<long double>());
            } catch (const std::exception& e) {
                throw std::invalid_argument("Non-numeric value found in JSON object for key: " + key);
            }
        }
        df.append_row(row_data);
    }

    return df;
}
