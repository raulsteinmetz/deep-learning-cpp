#include "TerminalLossDisplay.h"

TerminalLossDisplay::TerminalLossDisplay(const std::string& display_title, size_t epochs)
    : title(display_title), total_epochs(epochs), current_epoch(0) {}

void TerminalLossDisplay::update(double loss, size_t epoch) {
    current_epoch = epoch;
    std::cout << "\033[2J\033[H";
    std::cout << title << "\n\n";

    std::cout << "Epoch: " << current_epoch << " / " << total_epochs << "\n";
    std::cout << "Current Loss: " << std::fixed << std::setprecision(6) << loss << "\n";

    int progress_bar_width = 50;
    int bar_filled = static_cast<int>((static_cast<double>(current_epoch) / total_epochs) * progress_bar_width);

    std::cout << "Progress: [";
    for (int i = 0; i < bar_filled; ++i) std::cout << "=";
    for (int i = bar_filled; i < progress_bar_width; ++i) std::cout << " ";
    std::cout << "]\n";

    std::cout.flush();
}
