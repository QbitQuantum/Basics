// @pymethod |PyCImageList|SetBkColor|Sets the background color for an Image List.
PyObject *PyCImageList_SetBkColor( PyObject *self, PyObject *args )
{
	CImageList *pList;
	if (!(pList=PyCImageList::GetImageList(self)))
		return NULL;
	int col;
	// @pyparm int|color||The new background color.
	if (!PyArg_ParseTuple( args, "i:SetBkColor", &col))
		return NULL;
	GUI_BGN_SAVE;
	BOOL ok = pList->SetBkColor(col);
	GUI_END_SAVE;
	if (!ok)
		RETURN_ERR("SetBkColor failed");
	RETURN_NONE;
}