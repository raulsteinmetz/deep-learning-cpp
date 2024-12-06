#include "CSVDataFrameFactory.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

DataFrame CSVDataFrameFactory::create_dataframe(const std::string& f_path) const {
    std::ifstream file(f_path);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + f_path);
    }

    DataFrame df;
    std::string line;
    bool is_header = true;

    while (std::getline(file, line)) {
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;

        while (std::getline(ss, token, ',')) {
            tokens.push_back(token); // each token is a value between commas
        }

        if (is_header) { // first line of the csv should indicate the column names
            df.set_columns(tokens);
            is_header = false;
        } else { // every other line should be numeric values
            std::vector<long double> row;
            for (const auto& t : tokens) {
                try {
                    row.push_back(std::stold(t));
                } catch (const std::exception& e) {
                    throw std::invalid_argument("Non-numeric value found in data row");
                }
            }
            df.append_row(row);
        }
    }

    file.close();
    return df;
}
