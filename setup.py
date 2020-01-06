from distutils.core import setup
from Cython.Build import cythonize
import sys
import numpy as np


setup(
    ext_modules=cythonize([
        "pylib/math_cy.pyx",
        # "pylib/math.py",
        "pylib/sobel_cy.pyx"
    ], annotate=True, language_level=3),
    include_dirs=[np.get_include()]
)