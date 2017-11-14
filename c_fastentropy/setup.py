from distutils.core import setup, Extension
import numpy.distutils.misc_util

c_ext = Extension("_fastentropy", ["_fastentropy.c", "_sampen.c"])

setup(
    ext_modules=[c_ext],
    include_dirs=numpy.distutils.misc_util.get_numpy_include_dirs(),
)
