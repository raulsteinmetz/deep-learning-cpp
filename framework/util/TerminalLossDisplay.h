#ifndef TERMINALLOSSDISPLAY_H
#define TERMINALLOSSDISPLAY_H

#include "LossSubscriber.h"
#include <string>
#include <iostream>
#include <iomanip>

/**
 * @class TerminalLossDisplay
 * @brief Concrete subscriber for displaying loss updates in the terminal.
 */
class TerminalLossDisplay : public LossSubscriber {
private:
    std::string title;
    size_t total_epochs;
    size_t current_epoch;

public:
    /**
     * @brief Constructor for TerminalLossDisplay.
     * @param display_title The title to display in the terminal.
     * @param epochs The total number of epochs for training.
     */
    TerminalLossDisplay(const std::string& display_title, size_t epochs);

    /**
     * @brief Updates the terminal display with the current loss and epoch.
     * @param loss The updated loss value.
     * @param epoch The current epoch.
     */
    void update(double loss, size_t epoch);
};

#endif // TERMINALLOSSDISPLAY_H
