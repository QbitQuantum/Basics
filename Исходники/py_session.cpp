static PyObject* meth_eval_get_result(obj_Session* self, PyObject* args)
{
  char* b;
  int l;
  if (!PyArg_ParseTuple(args, "u#", &b, &l))
  {
    return NULL;
  }
  TPtrC text((TUint16*)b, l);

  TBuf<512> resultDes;
  TInt evalErrCode = 0;
  TInt errCode = self->iSession.EvalGetResult(text, evalErrCode, resultDes);
  if (errCode) {
    return SPyErr_SetFromSymbianOSErr(errCode);
  }
  return Py_BuildValue("(iu#)", evalErrCode, resultDes.Ptr(), resultDes.Length());
}