#ifndef JSONDATAFRAMEFACTORY_H
#define JSONDATAFRAMEFACTORY_H

#include "DataFrameFactory.h"
#include "DataFrame.h"
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

/**
 * @class JsonDataFrameFactory
 * @brief Concrete DataFrame creator, parses Json files.
 */
class JsonDataFrameFactory : public DataFrameFactory {
public:
    /**
     * @brief Creates a DataFrame from a Json file.
     * @param f_path Path to the Json file to be parsed.
     * @return A DataFrame object populated with data from the JSON file.
     * @throws std::runtime_error if the file cannot be opened or read.
     */
    DataFrame create_dataframe(const std::string& f_path) const override;
};

#endif // JSONDATAFRAMEFACTORY_H
