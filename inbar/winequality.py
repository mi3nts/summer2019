# -*- coding: utf-8 -*-

import pandas as pd
import matplotlib.pyplot as plt
from sklearn import linear_model
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error
# load dataset

data = pd.read_csv("../downloads/winequality.csv")
data.shape

def thing(x):
    return x - 2
# clean dataset
# remove null values if any
data[data.isnull()] = 0

data["free sulfur dioxide"] = data["free sulfur dioxide"].apply(lambda x: (x - 15)/10)
data["pH"] = data["pH"].apply(lambda x: (x - 3.5)*2)
data["thing"] = data["thing"].apply(lambda x: x-9)
data["total sulfur dioxide"] = data["total sulfur dioxide"].apply(lambda x: (x-100)/50)
data["fixed acidity"] = data["fixed acidity"].apply(lambda x: (x-8))
data["residual sugar"] = data["residual sugar"].apply(lambda x: (x-2))


plt.figure(0)
plt.hist(data["pH"])

# split into training and test sets
# predict quality of wine
train, test = train_test_split(data, test_size=.2)

train_in = train.loc[:, :"sulphates"]
train_out = train["quality"]

test_in = test.loc[:, :"sulphates"]
test_out = test["quality"]
reg=linear_model.LinearRegression().fit(train_in, train_out)

pred = reg.predict(test_in)

plt.figure(1)
plt.xlabel("quality")
plt.ylabel("prediction")
plt.plot(test_out, pred, 'o')

print("Linear reg error ", mean_squared_error(pred, test_out))
# create model = > neural network
# use test set to predict values
from sklearn.neural_network import MLPRegressor
nn = MLPRegressor(hidden_layer_sizes=(3,2), activation='relu', solver='lbfgs', alpha=0.001, 
             batch_size=10, learning_rate="constant", max_iter=5000, tol=0.0005, verbose=False)

nn.fit(train_in, train_out)
nn_pred = nn.predict(test_in)
nn_trained = nn.predict(train_in)
plt.figure(2)
plt.xlabel("quality")
plt.ylabel("prediction")
plt.plot(train_out, nn_trained, 'ro')
plt.plot(test_out, nn_pred, 'bo')

print("Neural Network error ", mean_squared_error(nn_pred, test["quality"]))
print("Neural Network trained error ", mean_squared_error(nn_trained, train["quality"]))

# Random Forest
from sklearn.ensemble import RandomForestRegressor
regr = RandomForestRegressor(max_depth=15, random_state=0, n_estimators=100)
regr.fit(train_in, train_out)
print(regr.feature_importances_)

rf_pred = regr.predict(test_in)

plt.figure(3)
plt.xlabel("quality")
plt.ylabel("prediction")
plt.plot(train_out, regr.predict(train_in), 'bo')
plt.plot(test_out, rf_pred, 'ro')

print("Random Forest error ", mean_squared_error(rf_pred, test_out))

