#ifndef CSVDATAFRAMEFACTORY_H
#define CSVDATAFRAMEFACTORY_H

#include "DataFrameFactory.h"
#include "DataFrame.h"
#include <string>

/**
 * @class CSVDataFrameFactory
 * @brief Concrete DataFrame creator, parses CSV files.
 */
class CSVDataFrameFactory : public DataFrameFactory {
public:
    /**
     * @brief Parses a CSV file and returns a DataFrame object.
     * @param f_path Path to the CSV file.
     * @return A DataFrame object with data from the CSV file.
     * @throws std::runtime_error if the file cannot be opened.
     * @throws std::invalid_argument if non-numeric values are found in the data rows.
     */
    DataFrame create_dataframe(const std::string& f_path) const override;
};

#endif // CSVDATAFRAMEFACTORY_H
