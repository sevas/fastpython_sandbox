
import pytest
import numpy as np
from pylib import mynumeric, math_cy
from pylib import mylib as mylib


@pytest.mark.benchmark(group="sum-of-ints")
def test_math(benchmark):
    benchmark(mynumeric.sum, 0, 1e7)


@pytest.mark.benchmark(group="sum-of-ints")
def test_math_cy(benchmark):

    benchmark(math_cy.sum, 0, 1e7)

@pytest.mark.benchmark(group="sum-of-ints")
def test_math_np(benchmark):
    values = np.arange(0, 1e7, dtype=np.int32)
    benchmark(np.sum, values)


@pytest.mark.benchmark(group="sum-of-ints")
def test_math_pb11_cppvec(benchmark):
    values = np.arange(0, 1e7, dtype=np.int32)
    benchmark(mylib.sum_int, values)


@pytest.mark.benchmark(group="sum-of-ints")
def test_math_pb11_eigenmat(benchmark):
    values = np.arange(0, 1e7, dtype=np.int32)
    benchmark(mylib.sum_eigen_i, values)


@pytest.mark.benchmark(group="sum-of-ints")
def test_math_pb11_pyarray(benchmark):
    values = np.arange(0, 1e7, dtype=np.int32)
    benchmark(mylib.sum_int_pyarray, values)
