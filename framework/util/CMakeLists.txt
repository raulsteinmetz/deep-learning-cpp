add_library(util
    LossPublisher.cpp
    TerminalLossDisplay.cpp
    EventManager.cpp
)

target_include_directories(util PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)