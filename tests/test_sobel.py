import pytest
import numpy as np
from pylib import sobel, sobel_cy
from pylib import mylib as mylib

from skimage import data
from skimage import filters

@pytest.fixture()
def im():
    yield data.camera()


def test_sobel_py(im, benchmark):
    out = np.zeros_like(im)
    benchmark(sobel.sobel, im, out)


def test_sobel_skimage(im, benchmark):
    benchmark(filters.sobel, im)


def test_sobel_cy(im, benchmark):
    out = np.zeros_like(im)
    benchmark(sobel_cy.sobel, im, out)