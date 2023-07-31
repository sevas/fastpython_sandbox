import numpy as np
import math as m
from numba import njit

k_x = np.array([
    [-1, 0, 1],
    [-2, 0, 2],
    [-1, 0, 1]])

k_y = np.array([
    [-1, -2, -1],
    [0, 0, 0],
    [1, 2, 1]])

neighbour_idx = np.array([
    [(-1, -1), (-1, 0), (-1, 1)],
    [(0, -1), (0, 0), (0, 1)],
    [(1, -1), (1, 0), (1, 1)],
])


@njit
def sobel(im, out):
    h, w = im.shape
    for y in range(1, h - 1):
        for x in range(1, w - 1):
            x_val = 0
            y_val = 0
            for yy in range(3):
                for xx in range(3):
                    dx, dy = neighbour_idx[yy, xx]
                    x_val += k_x[yy, xx] * im[y + dy, x + dx]
                    y_val += k_y[yy, xx] * im[y + dy, x + dx]

            out[y, x] = m.sqrt(x_val * x_val + y_val * y_val)
