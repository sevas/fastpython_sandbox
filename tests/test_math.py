
import pytest
import numpy as np
from pylib import math, math_cy
from pylib import mylib as mylib


def test_math(benchmark):
    benchmark(math.sum, 0, 1e7)


def test_math_cy(benchmark):

    benchmark(math_cy.sum, 0, 1e7)


def test_math_np(benchmark):
    values = np.arange(0, 1e7, dtype=np.int32)
    benchmark(np.sum, values)


def test_math_pb11_cppvec(benchmark):
    values = np.arange(0, 1e7, dtype=np.int32)
    benchmark(mylib.sum_int, values)


def test_math_pb11_eigenmat(benchmark):
    values = np.arange(0, 1e7, dtype=np.int32)
    benchmark(mylib.sum_eigen_i, values)

def test_math_pb11_pyarray(benchmark):
    values = np.arange(0, 1e7, dtype=np.int32)
    benchmark(mylib.sum_int_pyarray, values)
