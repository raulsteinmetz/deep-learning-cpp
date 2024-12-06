# Design Patterns Used

## 1. Factory Method

Used to create `DataFrame` objects from various file formats. CSV and Json factories were implemented.

#### Product Interface:
```cpp
   class DataFrame {
   private:
       std::vector<std::string> column_names;
       std::vector<std::vector<long double>> data;
   
   public:
       DataFrame() = default;
       void set_columns(const std::vector<std::string>& names);
       void append_row(const std::vector<long double>& row);
       const std::vector<std::string>& get_columns() const;
       const std::vector<std::vector<long double>>& get_data() const;
       size_t row_count() const;
       size_t column_count() const;
       DataFrame dataframe_from_column(const std::string& column) const;
       void drop_columns(const std::vector<std::string>& columns);
   };
   
```

#### Creator Interface:

```cpp
   class DataFrameFactory {
   public:
       virtual ~DataFrameFactory() = default;
       virtual DataFrame create_dataframe(const std::string& f_path) const = 0;
   };
   
```

#### Concrete Factories:
```cpp
   class JsonDataFrameFactory : public DataFrameFactory {
   public:
       DataFrame create_dataframe(const std::string& f_path) const override;
   };

```

```cpp
   class CSVDataFrameFactory : public DataFrameFactory {
   public:
       DataFrame create_dataframe(const std::string& f_path) const override;
   };

```

#### Use (in an utilitary class):

```cpp
   DataFrame DataFrameUtils::df_from_csv(const std::string& f_path) {
       CSVDataFrameFactory factory;
       return factory.create_dataframe(f_path);
   }
   
   DataFrame DataFrameUtils::df_from_json(const std::string& f_path) {
       JsonDataFrameFactory factory;
       return factory.create_dataframe(f_path);
   }
```

## 2. Iterator

Used to iterate the DataFrame, hiding implementation details.

#### Iterator Interface:

```cpp
   class Iterator {
   public:
       virtual bool hasMore() const = 0;
       virtual const std::vector<long double>& getNext() = 0;
       virtual void reset() = 0;
       virtual size_t size() const = 0;
       virtual ~Iterator() = default;
   };
```
#### Concrete iterator for the DataFrame data structure:

```cpp
   class DataFrameIterator : public Iterator {
   public:
       DataFrameIterator(const DataFrame& dataframe);
       bool hasMore() const override;
       const std::vector<long double>& getNext() override;
       void reset() override;
       size_t size() const override;
   
   private:
       const DataFrame& dataframe;
       size_t currentRowIndex;
   };
```

#### Use:

```cpp
   void test(Iterator& testLoader, Iterator& testTargetLoader) {
        long double totalLoss = 0.0;
        long double totalAccuracy = 0.0;
        size_t totalSamples = 0;

        testLoader.reset();
        testTargetLoader.reset();

        while (testLoader.hasMore() && testTargetLoader.hasMore()) {
            const auto& input = testLoader.getNext();
            const auto& target = testTargetLoader.getNext();

            auto prediction = model.forward(input);

            totalLoss += loss_function->compute_loss({prediction[0]}, {target[0]});
            totalAccuracy += calculate_single_accuracy(prediction[0], target[0]);

            ++totalSamples;
        }

        long double averageLoss = totalLoss / totalSamples;
        long double accuracyPercentage = (totalAccuracy / totalSamples) * 100.0L;

        std::cout << "Test Loss: " << averageLoss << "\n";
        std::cout << "Test Accuracy: " << accuracyPercentage << "%\n";
    }
```

## 3. Composite

Used for building a neural network (complex hierarchical structure), while treating individual componetents and compositions uniformely.

#### Component Interface (Base Class):

```cpp
   class Module {
   public:
       virtual ~Module() = default;
       virtual std::vector<long double> forward(const std::vector<long double>& inputs) = 0;
       virtual std::vector<long double> backward(const std::vector<long double>& gradients) = 0;
       virtual void update_parameters(long double learning_rate) = 0;
   };
```

#### Leaf Components (Concrete Modules):

```cpp
   class LinearLayer : public Module {
   private:
       size_t input_size;
       size_t output_size;
   
       std::vector<std::vector<long double>> weights;
       std::vector<long double> biases;
       std::vector<std::vector<long double>> gradients_weights;
       std::vector<long double> gradients_biases;
       std::vector<long double> inputs_cache;
   
   public:
       LinearLayer(size_t input_size, size_t output_size);
       std::vector<long double> forward(const std::vector<long double>& inputs) override;
       std::vector<long double> backward(const std::vector<long double>& gradients) override;
       void update_parameters(long double learning_rate) override;
   };
```

```cpp
   class ActivationLayer : public Module {
   private:
       std::function<std::vector<long double>(const std::vector<long double>&)> activation_func;
       std::function<std::vector<long double>(const std::vector<long double>&)> activation_derivative;
       std::vector<long double> inputs_cache;
   
   public:
       ActivationLayer(
           std::function<std::vector<long double>(const std::vector<long double>&)> func,
           std::function<std::vector<long double>(const std::vector<long double>&)> derivative);

       std::vector<long double> forward(const std::vector<long double>& inputs) override;
       std::vector<long double> backward(const std::vector<long double>& gradients) override;
       void update_parameters(long double learning_rate) override {}
   };

```

#### Composite Class (Sequential NN example):

```cpp
   class Sequential : public Module {
   private:
       std::vector<std::shared_ptr<Module>> modules;

   public:
       void add_module(const std::shared_ptr<Module>& module);
       std::vector<long double> forward(const std::vector<long double>& inputs) override;
       std::vector<long double> backward(const std::vector<long double>& gradients) override;
       void update_parameters(long double learning_rate) override;
   };
```

#### Use:

```cpp
   Sequential model;
   model.add_module(std::make_shared<LinearLayer>(data.column_count(), 64));
   model.add_module(std::make_shared<ActivationLayer>(Activations::relu, Activations::relu_derivative));
   model.add_module(std::make_shared<LinearLayer>(64, 32));
   model.add_module(std::make_shared<ActivationLayer>(Activations::relu, Activations::relu_derivative));
   model.add_module(std::make_shared<LinearLayer>(32, 1));
   model.add_module(std::make_shared<ActivationLayer>(Activations::sigmoid, Activations::sigmoid_derivative));

   auto prediction = model.forward(input);
   std::vector<long double> gradients(1);
   gradients[0] = (prediction[0] - target[0]);
   model.backward(gradients);
   model.update_parameters(learningRate);
```

## 4. Observer

Used to implement a decoupled mechanism for monitoring loss values during training.

#### Publisher (Event Manager):

```cpp
   class EventManager {
   private:
       std::unordered_map<std::string, std::vector<std::function<void(double)>>> listeners;
   
   public:
       void subscribe(const std::string& eventType, const std::function<void(double)>& listener);
       void unsubscribe(const std::string& eventType);
       void notify(const std::string& eventType, double data);
   };
```

#### Loss Publisher:

```
   class LossPublisher {
   private:
       EventManager eventManager;
       std::vector<double> epoch_losses;
   
   public:
       void publish_loss(double loss);
       const std::vector<double>& get_losses() const;
       EventManager& get_event_manager();
   };
```

#### Subscriber Interface:

```cpp
   class LossSubscriber {
   public:
       virtual ~LossSubscriber() = default;
       virtual void update(double loss) = 0;
   };
```

#### Concrete Subscriber (Terminal Display):

```cpp
   class TerminalLossDisplay : public LossSubscriber {
   private:
       std::string title;
       size_t total_epochs;
       size_t current_epoch;
   
   public:
       TerminalLossDisplay(const std::string& displayTitle, size_t epochs);
       void update(double loss) override;
       void update(double loss, size_t epoch);
   };
```

#### Use:

```cpp
   LearningFacade(const Sequential& model, std::shared_ptr<LossFunction> loss_function, size_t epochs)
        : model(model), loss_function(std::move(loss_function)), total_epochs(epochs) {
        auto terminal_display = std::make_shared<TerminalLossDisplay>("Training Progress", total_epochs);
        loss_publisher.get_event_manager().subscribe("loss_updated", [terminal_display, this](double loss) {
            terminal_display->update(loss, loss_publisher.get_losses().size());
        });
   }

   void train(Iterator& trainLoader, Iterator& targetLoader, long double learningRate) {
       for (size_t epoch = 1; epoch <= total_epochs; ++epoch) {
           long double totalLoss = 0.0;
           size_t totalSamples = 0;
   
           trainLoader.reset();
           targetLoader.reset();
   
           while (trainLoader.hasMore() && targetLoader.hasMore()) {
               const auto& input = trainLoader.getNext();
               const auto& target = targetLoader.getNext();
   
               auto prediction = model.forward(input);
               long double loss = loss_function->compute_loss({prediction[0]}, {target[0]});
               totalLoss += loss;
   
               std::vector<long double> gradients(1);
               gradients[0] = (prediction[0] - target[0]);
   
               model.backward(gradients);
               model.update_parameters(learningRate);
   
               ++totalSamples;
           }
   
           long double epochLoss = totalLoss / totalSamples;
           loss_publisher.publish_loss(epochLoss);
       }
   }

```

## 5. Facade

Used to abstract the learning loop and all of its components.

```cpp
   class LearningFacade {
   private:
       Sequential model;
       std::shared_ptr<LossFunction> loss_function;
       LossPublisher loss_publisher;
       size_t total_epochs;
   
       long double calculate_accuracy(long double prediction, long double target) const {
           long double pred = prediction >= 0.5L ? 1.0L : 0.0L;
           return pred == target ? 1.0L : 0.0L;
       }
   
   public:
       LearningFacade(const Sequential& model, std::shared_ptr<LossFunction> loss_function, size_t epochs)
           : model(model), loss_function(std::move(loss_function)), total_epochs(epochs) {
           auto terminal_display = std::make_shared<TerminalLossDisplay>("Training Progress", total_epochs);
           loss_publisher.get_event_manager().subscribe("loss_updated", [terminal_display, this](double loss) {
               terminal_display->update(loss, loss_publisher.get_losses().size());
           });
       }
       void train(Iterator& trainLoader, Iterator& targetLoader, long double learningRate) {
           for (size_t epoch = 1; epoch <= total_epochs; ++epoch) {
               long double totalLoss = 0.0;
               size_t totalSamples = 0;
   
               trainLoader.reset();
               targetLoader.reset();
   
               while (trainLoader.hasMore() && targetLoader.hasMore()) {
                   const auto& input = trainLoader.getNext();
                   const auto& target = targetLoader.getNext();
   
                   auto prediction = model.forward(input);
   
                   long double loss = loss_function->compute_loss({prediction[0]}, {target[0]});
                   totalLoss += loss;
   
                   std::vector<long double> gradients(1);
                   gradients[0] = (prediction[0] - target[0]);
   
                   model.backward(gradients);
                   model.update_parameters(learningRate);
   
                   ++totalSamples;
               }
   
               long double epochLoss = totalLoss / totalSamples;
               loss_publisher.publish_loss(epochLoss);
           }
       }
   
       void test(Iterator& testLoader, Iterator& testTargetLoader) {
           long double totalLoss = 0.0;
           long double totalAccuracy = 0.0;
           size_t totalSamples = 0;
   
           testLoader.reset();
           testTargetLoader.reset();
   
           while (testLoader.hasMore() && testTargetLoader.hasMore()) {
               const auto& input = testLoader.getNext();
               const auto& target = testTargetLoader.getNext();
   
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

```
