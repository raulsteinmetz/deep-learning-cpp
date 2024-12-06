#ifndef LEARNINGFACADE_H
#define LEARNINGFACADE_H

#include "SequentialNN.h"
#include "DataFrameIterator.h"
#include "LossPublisher.h"
#include "TerminalLossDisplay.h"
#include "LossFunction.h"
#include <memory>
#include <iostream>
#include <vector>
#include <iomanip>

/**
 * @class LearningFacade
 * @brief Facade for managing the learning and testing process.
 */
class LearningFacade {
private:
    Sequential model;
    std::shared_ptr<LossFunction> loss_function;
    LossPublisher loss_publisher;
    size_t total_epochs;

    /**
     * @brief Calculate accuracy based on a single prediction and target.
     * @param prediction The model's prediction.
     * @param target The ground truth label.
     * @return 1.0 if correct, 0.0 otherwise.
     */
    long double calculate_accuracy(long double prediction, long double target) const {
        long double pred = prediction >= 0.5L ? 1.0L : 0.0L;
        return pred == target ? 1.0L : 0.0L;
    }

public:
    /**
     * @brief Constructor for the LearningFacade.
     * @param model The model to train and test.
     * @param loss_function The loss function to use during training/testing.
     * @param epochs The total number of training epochs.
     */
    LearningFacade(const Sequential& model, std::shared_ptr<LossFunction> loss_function, size_t epochs)
        : model(model), loss_function(std::move(loss_function)), total_epochs(epochs) {
        auto terminal_display = std::make_shared<TerminalLossDisplay>("Training Progress", total_epochs);
        loss_publisher.get_event_manager().subscribe("loss_updated", [terminal_display](double loss, size_t epoch) {
            terminal_display->update(loss, epoch);
        });
    }

    /**
     * @brief Train the model with the given data and parameters.
     * @param train_loader Training data loader.
     * @param target_loader Target data loader.
     * @param learning_rate Learning rate for training.
     */
    void train(Iterator& train_loader, Iterator& target_loader, long double learning_rate) {
        for (size_t epoch = 1; epoch <= total_epochs; ++epoch) {
            long double totalLoss = 0.0;
            size_t totalSamples = 0;

            train_loader.reset();
            target_loader.reset();

            while (train_loader.has_more() && target_loader.has_more()) {
                const auto& input = train_loader.get_next();
                const auto& target = target_loader.get_next();

                auto prediction = model.forward(input);

                long double loss = loss_function->compute_loss({prediction[0]}, {target[0]});
                totalLoss += loss;

                std::vector<long double> gradients(1);
                gradients[0] = (prediction[0] - target[0]);

                model.backward(gradients);
                model.update_parameters(learning_rate);

                ++totalSamples;
            }

            long double epochLoss = totalLoss / totalSamples;
            loss_publisher.publish_loss(epochLoss, epoch);
        }
    }



    /**
     * @brief Test the model and compute accuracy.
     * @param test_loader Testing data loader.
     * @param target_loader Testing target loader.
     */
    void test(Iterator& test_loader, Iterator& target_loader) {
        long double totalLoss = 0.0;
        long double totalAccuracy = 0.0;
        size_t totalSamples = 0;

        test_loader.reset();
        target_loader.reset();

        while (test_loader.has_more() && target_loader.has_more()) {
            const auto& input = test_loader.get_next();
            const auto& target = target_loader.get_next();

            auto prediction = model.forward(input);

            totalLoss += loss_function->compute_loss({prediction[0]}, {target[0]});
            totalAccuracy += calculate_accuracy(prediction[0], target[0]);

            ++totalSamples;
        }

        long double averageLoss = totalLoss / totalSamples;
        long double accuracyPercentage = (totalAccuracy / totalSamples) * 100.0L;

        std::cout << "Test Loss: " << averageLoss << "\n";
        std::cout << "Test Accuracy: " << accuracyPercentage << "%\n";
    }
};

#endif // LEARNINGFACADE_H
