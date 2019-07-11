# -*- coding: utf-8 -*-

import numpy as np
import math
import time


INPUT_SIZE = 8
HIDDEN_SIZE = 4
OUTPUT_SIZE = 1

STEP_LEN = 0.5

# params
vs = np.random.random((INPUT_SIZE, HIDDEN_SIZE))
gamma = np.random.random((HIDDEN_SIZE))
ws = np.random.random((HIDDEN_SIZE, OUTPUT_SIZE))
ws = np.zeros((HIDDEN_SIZE, OUTPUT_SIZE))
theta = np.random.random((OUTPUT_SIZE))


# activation function
def sigmoid(x):
    return 1 / (1 + math.exp(-x))


# neural output
def neural(inputs, vs, gamma, ws, theta, f):
    outputs = np.zeros((len(theta)))
    bs = np.zeros((len(gamma)))
    # calc hidden output
    for h in range(len(gamma)):
        alpha = 0.0
        for i, input in enumerate(inputs):
            alpha += vs[i, h] * input
        bs[h] = f(alpha - gamma[h])
    # calc outputs
    for j in range(len(theta)):
        beta = 0.0
        for h, b in enumerate(bs):
            beta += ws[h, j] * b
        outputs[j] = f(beta - theta[j])
    return (outputs, bs)


# Ek
def ekf(ys, ys0):
    length = len(ys)
    res = 0.0
    for i in range(length):
        res += (ys[i] - ys0[i]) ** 2
    return res / 2


# gj
def gf(yj, yj0):
    return yj * (1 - yj) * (yj0 - yj)


# eh
def ef(bn, wh, gs):
    res = 0.0
    length = len(wh)
    for j in range(length):
        res += wh[j] * gs[j]
    return bn * (1 - bn) * res


# data
input_data0 = np.array([[1, 1, 1, 1, 1, 1, 0.697, 0.460],
                       [2, 1, 2, 1, 1, 1, 0.774, 0.376],
                       [2, 1, 1, 1, 1, 1, 0.634, 0.264],
                       [1, 1, 2, 1, 1, 1, 0.608, 0.318],
                       [3, 1, 1, 1, 1, 1, 0.556, 0.215],
                       [1, 2, 1, 1, 2, 2, 0.403, 0.237],
                       [2, 2, 1, 2, 2, 2, 0.481, 0.149],
                       [2, 2, 1, 1, 2, 1, 0.437, 0.211],
                       [2, 2, 2, 3, 2, 1, 0.666, 0.091],
                       [1, 3, 3, 1, 3, 2, 0.243, 0.267],
                       [3, 3, 3, 2, 3, 1, 0.245, 0.057],
                       [3, 1, 1, 2, 3, 2, 0.343, 0.099],
                       [1, 2, 1, 3, 1, 1, 0.639, 0.161],
                       [3, 2, 2, 3, 1, 1, 0.657, 0.198],
                       [2, 2, 1, 1, 2, 2, 0.360, 0.370],
                       [3, 1, 1, 2, 3, 1, 0.593, 0.042],
                       [1, 1, 2, 3, 2, 1, 0.719, 0.103]])
output_data = np.array([[1]] * 8 + [[-1]] * 9)
rounds = 100

# normalized
input_data = np.zeros(input_data0.shape)
for i,x in enumerate(input_data0):
    for j,y in enumerate(x):
        input_data[i, j] = y if y < 1 else ((y - 1.5) / 0.1)
        # input_data[i, j] = y if y < 1 else (y / 10.0 * 3)


# BP
for r in range(rounds):
    ek = 0.0
    for i, inputs in enumerate(input_data):
        ys, bs = neural(inputs, vs, gamma, ws, theta, sigmoid)
        ek += ekf(ys, output_data[i])

        gs = np.zeros((OUTPUT_SIZE))
        es = np.zeros((HIDDEN_SIZE))
        for j in range(OUTPUT_SIZE):
            gs[j] = gf(ys[j], output_data[i])
        for h in range(HIDDEN_SIZE):
            es[h] = ef(bs[h], ws[h, :], gs)

        ws += np.array([STEP_LEN * gj * bh for bh in bs for gj in gs]).reshape(HIDDEN_SIZE, OUTPUT_SIZE)
        theta += np.array([-STEP_LEN * gj for gj in gs])
        vs += np.array([STEP_LEN * eh * xi for xi in inputs for eh in es]).reshape(INPUT_SIZE, HIDDEN_SIZE)
        gamma += np.array([-STEP_LEN * eh for eh in es])
    print "round = ", r, ": Ek = ", ek
    time.sleep(0.1)


# print "vs: ", vs
# print "gamma: ", gamma
# print "ws: ", ws
# print "theta: ", theta

print "check: "
for inputs in input_data:
    y, b = neural(inputs, vs, gamma, ws, theta, sigmoid)
    print "y = ", y[0], y > 0.5
