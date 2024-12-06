add_library(data
    DataFrame.cpp
    CSVDataFrameFactory.cpp
    JsonDataFrameFactory.cpp
    DataFrameIterator.cpp
    DataFrameUtils.cpp
)

target_include_directories(data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
