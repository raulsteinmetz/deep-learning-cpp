#include "DataFrameIterator.h"

DataFrameIterator::DataFrameIterator(const DataFrame& dataframe)
    : dataframe(dataframe), currentRowIndex(0) {}

bool DataFrameIterator::has_more() const {
    return currentRowIndex < dataframe.row_count();
}

const std::vector<long double>& DataFrameIterator::get_next() {
    if (!has_more()) {
        throw std::out_of_range("No more rows in the DataFrame.");
    }
    return dataframe.get_data()[currentRowIndex++];
}

void DataFrameIterator::reset() {
    currentRowIndex = 0;
}

size_t DataFrameIterator::size() const {
    return dataframe.row_count();
}
