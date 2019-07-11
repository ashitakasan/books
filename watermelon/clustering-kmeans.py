# -*- coding: utf-8 -*-

import numpy as np
import random
import time


def kmeans(datas, us):
    clusters = [[] for i in range(0, len(us))]
    for i, d in enumerate(datas):
        dists = [distance(d, u) for u in us]
        index = np.argmin(dists)
        clusters[index].append(i)
    newus = [sum(datas[c])/len(c) for c in clusters]
    return clusters, newus


def distance(x1, x2):
    return np.sqrt(np.sum((np.array(x1) - np.array(x2)) ** 2))


datas = [
    [0.6970, 0.4600],
    [0.7740, 0.3760],
    [0.6340, 0.2640],
    [0.6080, 0.3180],
    [0.5560, 0.2150],
    [0.4030, 0.2370],
    [0.4810, 0.1490],
    [0.4370, 0.2110],
    [0.6660, 0.0910],
    [0.2430, 0.2670],
    [0.2450, 0.0570],
    [0.3430, 0.0990],
    [0.6390, 0.1610],
    [0.6570, 0.1980],
    [0.3600, 0.3700],
    [0.5930, 0.0420],
    [0.7190, 0.1030],
    [0.3590, 0.1880],
    [0.3390, 0.2410],
    [0.2820, 0.2570],
    [0.7480, 0.2320],
    [0.7140, 0.3460],
    [0.4830, 0.3120],
    [0.4780, 0.4370],
    [0.5250, 0.3690],
    [0.7510, 0.4890],
    [0.5320, 0.4720],
    [0.4730, 0.3760],
    [0.7250, 0.4450],
    [0.4460, 0.4590],
]

if __name__ == '__main__':
    old = None
    random.seed(time.time())
    us = random.sample(datas, 3)
    while True:
        Cs, us = kmeans(np.array(datas), us)
        if Cs == old:
            print Cs
            exit(0)
        old = Cs
        print Cs
        time.sleep(1)
