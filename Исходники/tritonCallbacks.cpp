static PyObject *Triton_getRegValue(PyObject *self, PyObject *reg)
{
  uint64 tritonReg;

  if (!PyLong_Check(reg) && !PyInt_Check(reg))
    return PyErr_Format(PyExc_TypeError, "getRegValue(): expected a register id (IDREF.REG) as argument");

  if (!ap.getCurrentCtxH())
    return PyErr_Format(PyExc_TypeError, "getRegValue(): Can't call getRegValue() right now. You must run the program before.");

  tritonReg = PyLong_AsLong(reg);

  if (tritonReg >= ID_XMM0 && tritonReg <= ID_XMM15){
    uint128 value = ap.getSSERegisterValue(tritonReg);
    return uint128ToPyLongObject(value);
  }

  return Py_BuildValue("k", ap.getRegisterValue(tritonReg));
}