from distutils.core import setup

setup(
    name='nonlineartools',
    version='0.1',
    packages=['entropy', '_fastentropy'],
    url='https://github.com/KubaRad/nonlineartools',
    license='MIT',
    author='Kuba Radlinski',
    author_email='kuba.radlinski@gmail.com',
    description='Tools for nonlinear calculations (entropy).',
    requires=['numpy', ]
)