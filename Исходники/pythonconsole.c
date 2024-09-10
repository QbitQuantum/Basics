static PyObject* emb_draw_fillrect(PyObject *self, PyObject *args)
{
	int x,y,w,h,r,g,b,a;
	a=255;
	if (!PyArg_ParseTuple(args, "IIIIIII|I:draw_fillrect",&x,&y,&w,&h,&r,&g,&b,&a))
		return NULL;
	if (vid_buf!=NULL)
	{
		fillrect(vid_buf,x,y,w,h,r,g,b,a);
		//fillrect
		return Py_BuildValue("i",1);
	}
	return Py_BuildValue("i",-1);
}