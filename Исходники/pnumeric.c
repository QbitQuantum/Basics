/*
 * Kalman filter process
 */
static PyObject *
kf_process(PyObject *self, PyObject *args, PyObject *kws)
{
    MatrixObject *A, *B, *C, *D, *x0, *P0, *Q, *R, *x, *P;
    Float *x_est, *y_est, *P_est;
    PyObject *out, *tmp, *tmp1, *x_est_out, *y_est_out, *P_est_out, *result;
    PyObject *mupdate_callback = NULL, *arglist;
    int i, j, k, n, p, q, datalength;
    MatrixObject *y, *u;

    static char *kwlist[] = {"A", "B", "C", "D", "y", "u", "x0", "P0", "Q", "R", "mupdate_callback", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kws, "O!O!O!O!O!O!O!O!O!O!|O:set_callback", kwlist,
            &MatrixType, &A,
            &MatrixType, &B,
            &MatrixType, &C,
            &MatrixType, &D,
            &MatrixType, &y,
            &MatrixType, &u,
            &MatrixType, &x0,
            &MatrixType, &P0,
            &MatrixType, &Q,
            &MatrixType, &R,
            &mupdate_callback))
        return NULL;

    if (A->rows != A->cols) {
        PyErr_SetString(PyExc_ValueError, "A must be a square matrix");
        return NULL;
    }

    n = A->rows;
    p = B->cols;
    q = C->rows;

    if (B->rows != n) {
        PyErr_SetString(PyExc_ValueError, "B must be Nxp matrix");
        return NULL;
    }
    if (C->cols != n) {
        PyErr_SetString(PyExc_ValueError, "C must be qxN matrix");
        return NULL;
    }
    if (D->rows != p || D->cols != q) {
        PyErr_SetString(PyExc_ValueError, "D must be pxq matrix");
        return NULL;
    }
    datalength = y->cols;
    if (y->cols != u->cols) {
        PyErr_SetString(PyExc_ValueError, "y and u data lengths does not match");
        return NULL;
    }
    if (y->rows != q) {
        PyErr_SetString(PyExc_ValueError, "y must be qxlength matrix");
        return NULL;
    }
    if (u->rows != p) {
        PyErr_SetString(PyExc_ValueError, "u must be pxlength matrix");
        return NULL;
    }
    if (x0->rows != n || x0->cols != 1) {
        PyErr_SetString(PyExc_ValueError, "x0 must be Nx1 matrix");
        return NULL;
    }
    if (P0->rows != n || P0->cols != n) {
        PyErr_SetString(PyExc_ValueError, "P0 must be NxN matrix");
        return NULL;
    }
    if (Q->rows != n || Q->cols != n) {
        PyErr_SetString(PyExc_ValueError, "Q must be NxN matrix");
        return NULL;
    }
    if (R->rows != q || R->cols != q) {
        PyErr_SetString(PyExc_ValueError, "R must be qxq matrix");
        return NULL;
    }
    if (!PyCallable_Check(mupdate_callback)) {
        if (mupdate_callback != NULL) {
            PyErr_SetString(PyExc_TypeError, "parameter must be callable");
            return NULL;
        }
    }

    x_est = m_new(n, datalength);
    y_est = m_new(n, datalength);
    P_est = m_new(n, n*datalength);

    if (mupdate_callback != NULL) {
        Py_XINCREF(mupdate_callback);  // Add a reference to new callback
        x = matrix_new(n, 1);
        P = matrix_new(n, n);
        // initialize x and P
        m_copy(x->data, x0->data, n, 1);
        m_copy(P->data, P0->data, n, n);

        for (i=0; i<datalength; i++) {
            tick(A->data, B->data, C->data, D->data,
                n, p, q,
                y->data+i*q, u->data+i*p,
                x->data, P->data,
                Q->data, R->data,
                x_est+i*n, y_est+i*q, P_est+i*n*n);
            // copy x and P values into output array
            m_copy(x->data, x_est+i*n, n, 1);
            m_copy(P->data, P_est+i*n*n, n, n);
            // update the matrixes
            arglist = Py_BuildValue("(i, O, O, O, O, O)", i, A, B, C, D, x);
            result = PyEval_CallObject(mupdate_callback, arglist);
            Py_DECREF(arglist);
        }
        Py_DECREF(x);
        Py_DECREF(P);
    } else { // model update not needed
        process(A->data, B->data, C->data, D->data,
                n, p, q, y->data, u->data, x0->data, P0->data, Q->data, R->data, datalength,
                x_est, y_est, P_est);
    }

    // create lists from matrixes
    x_est_out = PyList_New(datalength);
    for (i=0; i<datalength; i++) {
        tmp = PyList_New(n);
        for (j=0; j<n; j++) {
            PyList_SetItem(tmp, j, PyFloat_FromDouble( *(x_est+i*n+j) ));
        }
        PyList_SetItem(x_est_out, i, tmp);
    }
    y_est_out = PyList_New(datalength);
    for (i=0; i<datalength; i++) {
        tmp = PyFloat_FromDouble( *(y_est+i) );
        PyList_SetItem(y_est_out, i, tmp);
    }
    P_est_out = PyList_New(datalength);
    for (i=0; i<datalength; i++) {
        tmp = PyList_New(n);
        for (j=0; j<n; j++) {
            tmp1 = PyList_New(n);
            for (k=0; k<n; k++) {
                PyList_SetItem(tmp1, k, PyFloat_FromDouble( *(x_est+i*n+j*n+k) ));
            }
            PyList_SetItem(tmp, j, tmp1);
        }
        tmp = PyFloat_FromDouble( *(P_est+i) );
        PyList_SetItem(P_est_out, i, tmp);
    }

    m_free(x_est);
    m_free(y_est);
    m_free(P_est);

    out = PyTuple_New(3);
    PyTuple_SetItem(out, 0, x_est_out);
    PyTuple_SetItem(out, 1, y_est_out);
    PyTuple_SetItem(out, 2, P_est_out);
    Py_INCREF(out); // TODO add Py_INCREF every time when returning object from fnc

    return out;
}