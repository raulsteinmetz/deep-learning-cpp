#ifndef DATAFRAME_ITERATOR_H
#define DATAFRAME_ITERATOR_H

#include "Iterator.h"
#include "DataFrame.h"

/**
 * @class DataFrameIterator
 * @brief Concrete iterator for iterating rows of a DataFrame.
 */
class DataFrameIterator : public Iterator {
public:
    /**
     * @brief Constructor for DataFrameIterator.
     * @param dataframe Reference to the DataFrame to iterate.
     */
    DataFrameIterator(const DataFrame& dataframe);

    /**
     * @brief Checks if there are more rows to be iterated in the DataFrame.
     * @return True if there are more rows in the DataFrame, false otherwise.
     */
    bool has_more() const override;

    /**
     * @brief Returns the next row.
     * @return A reference to the next row.
     * @throws std::out_of_range if no more rows are available.
     */
    const std::vector<long double>& get_next() override;

    /**
     * @brief Resets the iterator to the first row.
     */
    void reset() override;

    /**
     * @brief Returns how many rows there are in the DataFrame.
     */
    size_t size() const override;

private:
    const DataFrame& dataframe;
    size_t currentRowIndex;
};

#endif // DATAFRAME_ITERATOR_H
