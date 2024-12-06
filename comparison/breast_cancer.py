import pandas as pd
import torch
from torch.utils.data import DataLoader, TensorDataset, random_split
from torch import nn, optim

def main():
    path = 'datasets/cancer/data.csv'
    target_column = 'Column_2'

    data = pd.read_csv(path)
    target = data[target_column]
    features = data.drop(columns=[target_column])

    X = torch.tensor(features.values, dtype=torch.float32)
    y = torch.tensor(target.values, dtype=torch.float32).unsqueeze(1)

    dataset = TensorDataset(X, y)
    train_size = int(0.8 * len(dataset))
    test_size = len(dataset) - train_size
    train_dataset, test_dataset = random_split(dataset, [train_size, test_size])

    batch_size = 32
    train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)
    test_loader = DataLoader(test_dataset, batch_size=batch_size, shuffle=False)

    class SimpleNN(nn.Module):
        def __init__(self, input_dim):
            super(SimpleNN, self).__init__()
            self.fc1 = nn.Linear(input_dim, 16)
            self.relu = nn.ReLU()
            self.fc2 = nn.Linear(16, 1)
            self.sigmoid = nn.Sigmoid()

        def forward(self, x):
            x = self.fc1(x)
            x = self.relu(x)
            x = self.fc2(x)
            x = self.sigmoid(x)
            return x

    model = SimpleNN(input_dim=X.shape[1])
    criterion = nn.BCELoss()
    optimizer = optim.Adam(model.parameters(), lr=0.001)

    num_epochs = 50
    for epoch in range(num_epochs):
        model.train()
        epoch_loss = 0
        for batch_X, batch_y in train_loader:
            predictions = model(batch_X)
            loss = criterion(predictions, batch_y)
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()
            epoch_loss += loss.item()

        print(f"Epoch {epoch + 1}/{num_epochs}, Loss: {epoch_loss / len(train_loader)}")

    model.eval()
    with torch.no_grad():
        correct = 0
        total = 0
        for batch_X, batch_y in test_loader:
            predictions = model(batch_X)
            predictions = (predictions >= 0.5).float()
            correct += (predictions == batch_y).sum().item()
            total += batch_y.size(0)

        print(f"Test Accuracy: {correct / total * 100:.2f}%")

if __name__ == '__main__':
    main()
