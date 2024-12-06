#ifndef DATAFRAMEFACTORY_H
#define DATAFRAMEFACTORY_H

#include "DataFrame.h"

/**
 * @class DataFrameFactory
 * @brief Abstract creator in factory method.
 */
class DataFrameFactory {
public:
    /**
     * @brief Virtual destructor for the DataFrameFactory.
     */
    virtual ~DataFrameFactory() = default;

    /**
     * @brief Creates a DataFrame from the specified file.
     * @param f_path Path to the file to be parsed.
     * @return A DataFrame object populated with data from the file.
     */
    virtual DataFrame create_dataframe(const std::string& f_path) const = 0;
};

#endif // DATAFRAMEFACTORY_H
