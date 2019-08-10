#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Aug  9 10:55:50 2019

@author: s243476
"""
import pandas as pd
import matplotlib.pyplot as plt
from sklearn import linear_model
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error

# load dataset
data = pd.read_csv("../downloads/calibrate.csv")
data.shape
data = data.iloc[:, 1:]

def normalize(col):
    maxVal = col.max()
    minVal = col.max()
    avgVal = (maxVal + minVal)/2
    interval = (maxVal - minVal)/2
    return (col-avgVal)/interval

# clean dataset
# remove null values if any
data[data.isnull()] = 0


col = data.head()
for i in list(col):
    data["C4H10_loRa"] = normalize(data["C4H10_loRa"])
    
plt.figure(0)
plt.hist(data["C4H10_loRa"])

#data["C4H10_loRa"] = data["C4H10_loRa"]/1000
#data["NO2_loRa"] = (data["NO2_loRa"]-4.5)*2
#data["CH4_loRa"] = (data["CH4_loRa"]-500)/200
#data["H2_loRa"] = (data["H2_loRa"]-900)/30
#data["P1_lpo_loRa"] = (data["P1_lpo_loRa"])/100000
#data["P1_conc_loRa"] = (data["P1_conc_loRa"])/500
#data["P2_lpo_loRa"] = (data["P2_lpo_loRa"])/100000
#data["P2_conc_loRa"] = (data["P2_conc_loRa"]-500)/500
#data["Temperature_loRa"] = (data["Temperature_loRa"]-22)/10
#data["Pressure_loRa"] = (data["Pressure_loRa"]-98868)/50
#data["Humidity_loRa"] = (data["Humidity_loRa"]-40)/40
#data["Humidity_loRa"] = (data["Humidity_loRa"]-40)/40

# split into training and test sets
# predict quality of wine
train, test = train_test_split(data, test_size=.2)

train_in = train.loc[:, "NH3_loRa":"Humidity_loRa"]
train_out = train.loc[:, "pm10_grimm":"alveolic_grimm"]

train_in[train_in > 5] = 5
train_in[train_in < -5] = -5

test_in = test.loc[:, "NH3_loRa":"Humidity_loRa"]
test_out = test.loc[:, "pm10_grimm":"alveolic_grimm"]

test_in[test_in > 5] = 5
test_in[test_in < -5] = -5

reg=linear_model.LinearRegression().fit(train_in, train_out)

lr_pred = reg.predict(test_in)
lr_train_pred = reg.predict(train_in)

plt.figure(1)
plt.xlabel("pm10_grimm")
plt.ylabel("prediction")
print(lr_pred.shape)
x = test_out["pm10_grimm"]
y = lr_pred[:, 0]
plt.plot(train_out["pm10_grimm"], lr_train_pred[:, 0], 'ro')
plt.plot(x, y, 'bo')

print("Linear reg error ", mean_squared_error(lr_pred, test_out))
# create model = > neural network
# use test set to predict values
from sklearn.neural_network import MLPRegressor
nn = MLPRegressor(hidden_layer_sizes=(4, 4), activation='relu', solver='lbfgs', alpha=0.001, 
             batch_size=30, max_iter=5000, tol=0.005, verbose=False)

nn.fit(train_in, train_out)
nn_pred = nn.predict(test_in)
nn_train_pred = nn.predict(train_in)

plt.figure(2)
plt.xlabel("pm10_grimm")
plt.ylabel("prediction")
x = test_out["pm10_grimm"]
y = nn_pred[:, 0]
plt.plot(train_out["pm10_grimm"], nn_train_pred[:, 0], 'ro')
plt.plot(x, y, 'bo')

print("Neural Network error ", mean_squared_error(nn_pred, test_out))

# Random Forest
from sklearn.ensemble import RandomForestRegressor
regr = RandomForestRegressor(max_depth=10, random_state=0, n_estimators=100)
regr.fit(train_in, train_out)
print(regr.feature_importances_)

rf_pred = regr.predict(test_in)
rf_train_pred = regr.predict(train_in)

plt.figure(3)
plt.xlabel("pm10_grimm")
plt.ylabel("prediction")
x = test_out["pm10_grimm"]
y = rf_pred[:, 0]

plt.plot(train_out["pm10_grimm"], rf_train_pred[:, 0], 'ro')
plt.plot(x, y, 'bo')

print("Random Forest error ", mean_squared_error(rf_pred, test_out))
