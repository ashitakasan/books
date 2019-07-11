# -*- coding: utf-8 -*-

import numpy as np
import time


attrs = 2
bate_base = np.ones([attrs + 1]) / 2          # (w;b) 初值


def probability1(x1, bate):
    exponent = np.dot(bate.T, x1)
    exp = np.exp(exponent)
    return exp / (1 + exp)


def first_derivative(xs, ys, bate):
    result = np.zeros(attrs + 1)
    length = len(ys)
    for i in range(length):
        x = xs[i, :]
        y = ys[i]
        xi = np.hstack((x, 1))
        p1 = probability1(xi, bate)
        result += xi * np.array([y - p1])
    return -result


def second_derivative(xs, bate):
    result = np.zeros([attrs + 1, attrs + 1])
    length = len(ys)
    for i in range(length):
        x = xs[i, :]
        xi = np.hstack((x, 1))
        xi.shape = attrs+1, 1
        p1 = probability1(xi, bate)
        result += np.dot(xi, xi.T) * p1 * (1 - p1)
    return result


def bate_iter(xs, ys, t, bate=None):
    if t <= 1:
        return bate_base
    else:
        if bate is None:
            bate = bate_iter(xs, ys, t-1)
        first = first_derivative(xs, ys, bate)
        second = second_derivative(xs, bate)
        inv = np.linalg.inv(second)
        return bate - np.dot(inv, first)


xs = np.array([[0.697, 0.460],
               [0.774, 0.376],
               [0.634, 0.264],
               [0.608, 0.318],
               [0.556, 0.215],
               [0.403, 0.237],
               [0.481, 0.149],
               [0.437, 0.211],
               [0.666, 0.091],
               [0.243, 0.267],
               [0.245, 0.057],
               [0.343, 0.099],
               [0.639, 0.161],
               [0.657, 0.198],
               [0.360, 0.370],
               [0.593, 0.042],
               [0.719, 0.103]])
ys = np.array([1] * 8 + [0] * 9)

# print first_derivative(xs, ys.T, bate_base)
# print second_derivative(xs, bate_base)

# print bate_iter(xs, ys, 10)

bate = None
for i in range(10):
    bate = bate_iter(xs, ys, i, bate)
    print bate
    time.sleep(1)

w = np.array([3.15832966, 12.52119579])
b = np.array([-4.42886451])

for x in xs:
    x.shape = attrs, 1
    print np.dot(w, x) + b
