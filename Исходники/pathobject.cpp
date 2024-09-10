static PyObject* path_transform(PyObject* self, PyObject* args) {
  Path* x = ((PathObject*)self)->m_x.get();
  PyObject* py_trans;
  int in_place = 0;
  if (PyArg_ParseTuple(args, "O|i", &py_trans, &in_place) <= 0)
    return 0;
  if (!is_TransformationObject(py_trans)) {
    PyErr_SetString(PyExc_TypeError, "transform requires a transformation object");
    return 0;
  }
  Transformation* trans = ((TransformationObject*)py_trans)->m_x;
  if (in_place) {
    x->transform_in_place(*trans);
    Py_INCREF(Py_None);
    return Py_None;
  } else {
    return create_PathObject(x->transform(*trans));
  }
}