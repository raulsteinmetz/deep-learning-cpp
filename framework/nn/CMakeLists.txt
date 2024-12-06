add_library(nn
    LinearLayer.cpp
    SequentialNN.cpp
    Activations.cpp
    ActivationLayer.cpp
    BCELoss.cpp
)

target_include_directories(data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
