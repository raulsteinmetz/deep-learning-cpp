#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <vector>
#include <string>
#include <stdexcept>
#include <memory>
#include "IterableCollection.h"
#include "Iterator.h"

/**
 * @class DataFrame
 * @brief Tabular data for deep learning. Implements IterableCollection.
 */
class DataFrame : public IterableCollection {
private:
    std::vector<std::string> column_names;
    std::vector<std::vector<long double>> data;

public:
    /**
     * @brief Default constructor for DataFrame.
     */
    DataFrame() = default;

    /**
     * @brief Sets the column names of the DataFrame.
     * @param names A vector of strings representing column names.
     */
    void set_columns(const std::vector<std::string>& names);

    /**
     * @brief Adds a row to the DataFrame.
     * @param row A vector of long doubles representing a row of data.
     * @throws std::invalid_argument if the row size does not match the column count.
     */
    void append_row(const std::vector<long double>& row);

    /**
     * @brief Returns the column names of the DataFrame.
     * @return A vector of strings representing column names.
     */
    const std::vector<std::string>& get_columns() const;

    /**
     * @brief Returns the data matrix stored in the DataFrame.
     * @return A vector of vectors of long doubles.
     */
    const std::vector<std::vector<long double>>& get_data() const;

    /**
     * @brief Returns the number of rows in the DataFrame.
     * @return The row count as a size_t.
     */
    size_t row_count() const;

    /**
     * @brief Returns the number of columns in the DataFrame.
     * @return The column count as a size_t.
     */
    size_t column_count() const;

    /**
     * @brief Creates a new DataFrame from a column.
     * @param column The name of the column.
     * @return A unique pointer to a new DataFrame containing only the selected column.
     * @throws std::invalid_argument if the column does not exist.
     */
    std::unique_ptr<DataFrame> dataframe_from_column(const std::string& column) const;

    /**
     * @brief Drops one or more columns from the DataFrame.
     * @param columns A vector of column names to drop.
     * @throws std::invalid_argument if any column does not exist.
     */
    void drop_columns(const std::vector<std::string>& columns);

    /**
     * @brief Creates an iterator for the DataFrame.
     * Implements IterableCollection interface.
     * @return A unique pointer to a DataFrameIterator.
     */
    std::unique_ptr<Iterator> create_iterator() const override;
};

#endif // DATAFRAME_H
