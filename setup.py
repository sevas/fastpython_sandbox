from distutils.core import setup
from Cython.Build import cythonize
import numpy as np


setup(
    name="pylib",
    version="0.0.1",
    ext_modules=cythonize([
        "pylib/math_cy.pyx",
        # "pylib/math.py",
        "pylib/sobel_cy.pyx"
    ], annotate=True, language_level=3),
    include_dirs=[np.get_include()]
)