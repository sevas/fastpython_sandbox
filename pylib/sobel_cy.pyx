import numpy as np
cimport numpy as np
from libc.math cimport sqrt


_k_x = np.array([
    -1, 0, 1,
    -2, 0, 2,
    -1, 0, 1
], dtype=np.intc).reshape(3, 3)

cdef int[:,:] k_x = _k_x


_k_y = np.array([
    -1, -2, -1,
     0, 0, 0,
     1, 2, 1], dtype=np.intc).reshape(3, 3)

cdef int[:,:] k_y = _k_y


_neighbour_idx = np.array([
    [(-1, -1), (-1, 0), (-1, 1)],
    [( 0, -1), ( 0, 0), ( 0, 1)],
    [( 1, -1), ( 1, 0), ( 1, 1)],
], dtype=np.intc).reshape(3, 3, 2)

cdef int[:,:,:] neighbour_idx = _neighbour_idx



cpdef sobel(np.ndarray[unsigned char, ndim=2] im, np.ndarray[unsigned char, ndim=2] out):
    cdef int h = im.shape[0]
    cdef int w = im.shape[1]
    cdef int x_val = 0
    cdef int y_val = 0
    cdef int dx, dy
    cdef int x, y, xx, yy

    for y in range(1, h-1):
        for x in range(1, w-1):
            x_val = 0
            y_val = 0
            for yy in range(3):
                for xx in range(3):
                    dx = neighbour_idx[yy, xx][0]
                    dy = neighbour_idx[yy, xx][1]

                    x_val += k_x[yy, xx] * im[y+dy, x+dx]
                    y_val += k_y[yy, xx] * im[y+dy, x+dx]

            out[y, x] = int(sqrt(x_val*x_val + y_val*y_val))