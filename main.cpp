#include "DataFrameUtils.h"
#include "DataFrameIterator.h"
#include "SequentialNN.h"
#include "LinearLayer.h"
#include "ActivationLayer.h"
#include "Activations.h"
#include "LearningFacade.h"
#include "BCELoss.h"

#include <iostream>
#include <memory>

int main() {
    try {
        std::string file_path = "../datasets/credit/data.csv";
        DataFrame data = DataFrameUtils::df_from_csv(file_path);
        
        std::unique_ptr<DataFrame> target = data.dataframe_from_column("default payment next month");
        data.drop_columns({"default payment next month"});

        float test_split_ratio = 0.2f;
        auto [training_data, testing_data, training_target, testing_target] =
            DataFrameUtils::train_test_split(data, *target, test_split_ratio);

        auto train_loader = training_data.create_iterator();
        auto target_loader = training_target.create_iterator();
        auto test_loader = testing_data.create_iterator();
        auto test_target_loader = testing_target.create_iterator();

        Sequential model;
        model.add_module(std::make_shared<LinearLayer>(data.column_count(), 64));
        model.add_module(std::make_shared<ActivationLayer>(Activations::tanh, Activations::tanh_derivative));
        model.add_module(std::make_shared<LinearLayer>(64, 32));
        model.add_module(std::make_shared<ActivationLayer>(Activations::tanh, Activations::tanh_derivative));
        model.add_module(std::make_shared<LinearLayer>(32, 1));
        model.add_module(std::make_shared<ActivationLayer>(Activations::sigmoid, Activations::sigmoid_derivative));

        auto loss_function = std::make_shared<BinaryCrossEntropyLoss>();

        LearningFacade learning_facade(model, loss_function, 100);

        std::cout << "Starting training process..." << std::endl;
        learning_facade.train(*train_loader, *target_loader, 0.01L);

        std::cout << "Starting testing process..." << std::endl;
        learning_facade.test(*test_loader, *test_target_loader);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
