/* method (t, b) = rand_asym(mu, b_lo, b_up, dt, n[, seed]) */
static PyObject* ddmmod_rand_asym(PyObject* self, PyObject* args)
{
    /* process arguments */
    PyArrayObject *py_mu, *py_b_lo, *py_b_up;
    double dt;
    int n, rngseed = 0;
    if (!PyArg_ParseTuple(args, "O!O!O!di|i", &PyArray_Type, &py_mu,
                          &PyArray_Type, &py_b_lo, &PyArray_Type, &py_b_up,
                          &dt, &n, &rngseed))
        return NULL;
    if (!(is1DDoubleArray(py_mu) && 
          is1DDoubleArray(py_b_lo) && is1DDoubleArray(py_b_up)))
        return NULL;
    if (dt <= 0.0) {
        PyErr_SetString(PyExc_ValueError, "dt needs to be larger than 0");
        return NULL;
    }
    if (n <= 0) {
        PyErr_SetString(PyExc_ValueError, "n needs to be larger than 0");
        return NULL;
    }
    ExtArray mu(ExtArray::shared_noowner((double*) PyArray_DATA(py_mu)),
                PyArray_DIM(py_mu, 0));
    ExtArray b_lo(ExtArray::shared_noowner((double*) PyArray_DATA(py_b_lo)),
                   PyArray_DIM(py_b_lo, 0));
    ExtArray b_up(ExtArray::shared_noowner((double*) PyArray_DATA(py_b_up)),
                   PyArray_DIM(py_b_up, 0));
    if (b_lo[0] >= 0.0) {
        PyErr_SetString(PyExc_ValueError, "b_lo[0] needs to be negative");
        return NULL;
    }
    if (b_up[0] <= 0.0) {
        PyErr_SetString(PyExc_ValueError, "b_up[0] needs to be positive");
        return NULL;
    }

    /* get output length and reserve space */
    npy_intp out_size[1] = { n };
    PyObject* py_t = PyArray_SimpleNew(1, out_size, NPY_DOUBLE);
    if (py_t == NULL) return NULL;
    PyObject* py_b = PyArray_SimpleNew(1, out_size, NPY_BOOL);
    if (py_b == NULL) {
        Py_DECREF(py_t);
        return NULL;
    }
    npy_double* t = (npy_double*) PyArray_DATA((PyArrayObject*) py_t);
    npy_bool* b = (npy_bool*) PyArray_DATA((PyArrayObject*) py_b);

    /* perform sampling */
    DMBase* dm = DMBase::create(mu, ExtArray::const_array(1.0), b_lo, b_up,
                                ExtArray::const_array(0.0), ExtArray::const_array(0.0), dt);
    DMBase::rngeng_t rngeng;
    if (rngseed == 0) rngeng.seed(std::random_device()());
    else rngeng.seed(rngseed);
    for (int i = 0; i < n; ++i) {
        DMSample s = dm->rand(rngeng);
        t[i] = s.t();
        b[i] = s.upper_bound() ? NPY_TRUE : NPY_FALSE;
    }
    delete dm;

    /* create tuple to return */
    PyObject* py_tuple = PyTuple_New(2);
    if (py_tuple == NULL) goto memory_fail;
    PyTuple_SET_ITEM(py_tuple, 0, py_t);
    PyTuple_SET_ITEM(py_tuple, 1, py_b);
    return py_tuple;

memory_fail:
    Py_DECREF(py_t);
    Py_DECREF(py_b);
    PyErr_SetString(PyExc_MemoryError, "out of memory");
    return NULL;
}