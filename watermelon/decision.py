# -*- coding: utf-8 -*-

import numpy as np
import math

from collections import Counter


class Node(object):
    name = None
    leaf = False
    label = None
    value = None
    children = None

    def __str__(self, level=0):
        res = str(self.value) + ' --> ' if self.value else ""
        res += self.name + ': '
        res += "好瓜" if self.label else "坏瓜" if self.leaf else ""
        res += '\n'
        if not self.children:
            return '\t' * level + res
        for c in self.children:
            res += c.__str__(level+1)
        return '\t' * level + res


def entf(D):
    ys = [xy[1] for xy in D] if D else None
    labels = Counter(ys)
    length = len(D)
    res = 0.0
    for x,c in labels.items():
        pk = float(c) / length
        res += pk * math.log(pk, 2)
    return -res


def gainf(D, a):
    ent = entf(D)
    xas = [xy[0][a] for xy in D] if D else None
    label_as = Counter(xas)
    tmpD = {x:[] for x in label_as}
    for d in D:
        tmpD[d[0][a]].append(d)

    length = len(D)
    res = 0.0
    for a,ds in tmpD.items():
        res += float(len(ds)) / length * entf(ds)
    return ent - res


def generate(D, A):
    def same_in_A(D, A):
        if not D:
            return True
        tmp = D[0][0]
        for xy in D:
            if any(tmp[A] != xy[0][A]):
                return False
        return True

    def divide_by_a(D, a_index):
        avs = set()
        for d in D:
            avs.add(d[0][a_index])
        tmpD = {x: [] for x in avs}
        for d in D:
            tmpD[d[0][a_index]].append(d)
        return tmpD

    node = Node()
    ys = [xy[1] for xy in D] if D else None
    if ys and (sum(ys) == 0 or sum(ys) == len(ys)):
        node.leaf = True
        node.label = sum(ys) == len(ys)
        node.name = "叶节点"
        return node

    if not A or same_in_A(D, A):
        trues = sum(ys)
        node.leaf = True
        node.label = trues >= len(ys) - trues
        node.name = "叶节点"
        return node

    gains = [gainf(D, a) for a in A]
    max_gain = max(gains)
    a_index = gains.index(max_gain)
    avs = set()
    for d in D:
        avs.add(d[0][a_index])
    dvs = divide_by_a(D, a_index)
    children = []
    for av, dv in dvs.items():
        child = Node()
        if not dv:
            trues = sum(ys)
            child.leaf = True
            child.label = trues >= len(ys) - trues
        else:
            _A = A[:]
            _A.remove(_A[a_index])
            child = generate(dv, _A)
        child.value = av
        children.append(child)

    node.children = children
    node.name = name_A[A[a_index]]
    return node


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
input_data = input_data0[:, 0:6]
output_data = np.array([True] * 8 + [False] * 9)

A = range(0, input_data.shape[1])
D = zip(input_data, output_data)
name_A = {0: "色泽", 1: "根蒂", 2: "敲声", 3: "纹理", 4: "脐部", 5: "触感"}

root = generate(D, A)

print root
