// @pymethod |PyCPropertySheet|EndDialog|Closes the dialog, with the specified result.
PyObject *ui_propsheet_end_dialog( PyObject *self, PyObject *args )
{
	CPropertySheet *pPS = pPS=GetPropSheet(self);
	if (!pPS) return NULL;
	int result;
	// @pyparm int|result||The result to be returned by DoModal.
	if (!PyArg_ParseTuple( args, "i", &result))
		return NULL;
	GUI_BGN_SAVE;
	pPS->EndDialog(result);
	GUI_END_SAVE;
	RETURN_NONE;
}