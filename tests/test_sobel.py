import pytest
import numpy as np
from pylib import sobel, sobel_cy, sobel_py, sobel_nb, sobel_nb_aot_built
# from pylib import mylib as mylib

from skimage import data
from skimage import filters


@pytest.fixture()
def im():
    yield data.camera()


@pytest.mark.benchmark(group="sobel-filter")
def test_sobel_py_cythonized(im, benchmark):
    out = np.zeros_like(im)
    benchmark(sobel.sobel, im, out)


@pytest.mark.benchmark(group="sobel-filter")
def test_sobel_py(im, benchmark):
    out = np.zeros_like(im)
    benchmark(sobel_py.sobel, im, out)


@pytest.mark.benchmark(group="sobel-filter")
def test_sobel_skimage(im, benchmark):
    benchmark(filters.sobel, im)


@pytest.mark.benchmark(group="sobel-filter")
def test_sobel_cy(im, benchmark):
    out = np.zeros_like(im)
    benchmark(sobel_cy.sobel, im, out)


@pytest.mark.benchmark(group="sobel-filter")
def test_sobel_numba(im, benchmark):
    out = np.zeros_like(im)
    benchmark(sobel_nb.sobel, im, out)


@pytest.mark.benchmark(group="sobel-filter")
def test_sobel_numba_aot(im, benchmark):
    out = np.zeros_like(im)
    benchmark(sobel_nb_aot_built.sobel, im, out)


#
# @pytest.mark.benchmark(group="sobel-filter")
# def test_sobel_cpp_pb11(im, benchmark):
#     out = np.zeros_like(im)
#     benchmark(mylib.sobel, im, out)
