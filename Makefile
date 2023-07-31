


cythonize: pylib/*.pyx
	conda run -n py311 python setup.py build_ext --inplace

numba_aot: pylib/sobel_nb_aot.py
	conda run -n py311 python pylib/sobel_nb_aot.py

all: cythonize
