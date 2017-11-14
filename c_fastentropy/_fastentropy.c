#include <Python.h>
#include <numpy/arrayobject.h>
#include "_sampen.h"

static char module_docstring[] =
    "This module provides an interface for calculating Sample Entropy using C.";
static char _sampen_docstring[] =
    "Calculate the Sample Entropy.";

static PyObject *fastentropy__sampen(PyObject *self, PyObject *args);

static PyMethodDef module_methods[] = {
    {"_sampen", fastentropy__sampen, METH_VARARGS, _sampen_docstring},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC PyInit__fastentropy(void)
{
    
    PyObject *module;
    static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "_fastentropy",
        module_docstring,
        -1,
        module_methods,
        NULL,
        NULL,
        NULL,
        NULL
    };
    module = PyModule_Create(&moduledef);
    if (!module) return NULL;

    /* Load `numpy` functionality. */
    import_array();

    return module;
}

static PyObject *fastentropy__sampen(PyObject *self, PyObject *args)
{
    double r;
    int m;
	PyObject *x_obj;

    /* Parse the input tuple */
    if (!PyArg_ParseTuple(args, "Oid", &x_obj, &m, &r))
        return NULL;

    /* Interpret the input objects as numpy arrays. */
    PyObject *x_array = PyArray_FROM_OTF(x_obj, NPY_DOUBLE, NPY_IN_ARRAY);
	

    /* If that didn't work, throw an exception. */
    if (x_array == NULL) {
        Py_XDECREF(x_array);
        return NULL;
    }

    /* How many data points are there? */
    int N = (int)PyArray_DIM(x_array, 0);

    /* Get pointers to the data as C-types. */
    double *x    = (double*)PyArray_DATA(x_array);

    /* Call the external C function to compute the sample entropy. */
    double value = _sampen(x, N, m, r);

    /* Clean up. */
    Py_DECREF(x_array);

    /* if (value < 0.0) {
        PyErr_SetString(PyExc_RuntimeError,
                    "SampEn returned an impossible value.");
        return NULL;
    }
	*/
	
    /* Build the output tuple */
    PyObject *ret = Py_BuildValue("d", value);
    return ret;
}