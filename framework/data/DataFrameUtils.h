#ifndef DATAFRAME_UTILS_H
#define DATAFRAME_UTILS_H

#include "DataFrame.h"
#include <tuple>

/**
 * @class DataFrameUtils
 * @brief Utility functions for working with DataFrames.
 */
class DataFrameUtils {
public:
    /**
     * @brief Creates a DataFrame from a CSV file.
     * @param f_path File path of the CSV.
     * @return A DataFrame loaded from the CSV file.
     */
    static DataFrame df_from_csv(const std::string& f_path);

    /**
     * @brief Creates a DataFrame from a JSON file.
     * @param f_path File path of the JSON.
     * @return A DataFrame loaded from the JSON file.
     */
    static DataFrame df_from_json(const std::string& f_path);

    /**
     * @brief Splits data and target into training and testing datasets.
     * @param data The input data.
     * @param target The target data.
     * @param test_ratio Ratio of data to be used for testing.
     * @return A tuple containing training data, testing data, training target, and testing target.
     */
    static std::tuple<DataFrame, DataFrame, DataFrame, DataFrame>
    train_test_split(const DataFrame& data, const DataFrame& target, float test_ratio);
};

#endif // DATAFRAME_UTILS_H
