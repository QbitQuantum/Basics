// @pymethod int|PyCRgn|GetRgnBox|Retrieves the coordinates of the bounding rectangle of the CRgn object
// Return Values: the bounding rectangle as a tuple (l,t,r,b)
PyObject *
PyCRgn::get_rgn_box(PyObject *self, PyObject *args)
	{
	CRgn *pRgn = PyCRgn::GetRgn(self);
	if (!pRgn) return NULL;

	CHECK_NO_ARGS2(args,GetRgnBox);

	RECT rect = {0,0,0,0};
	int result=pRgn->GetRgnBox(&rect);

	return Py_BuildValue("i(iiii)", result, rect.left, rect.top, rect.right, rect.bottom);
	}