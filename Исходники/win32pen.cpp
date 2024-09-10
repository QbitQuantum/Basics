// @pymethod <o PyCPen>|win32ui|CreatePen|Creates a <o PyCPen> object.
/*static*/ PyObject *
ui_pen_object::create (PyObject *self, PyObject *args)
{
  int n_pen_style;
  int n_width;
  long cr_color;
  LOGPEN lp;
  
  if (!PyArg_ParseTuple (args, "iil",
						 &n_pen_style, // @pyparm int|style||The pen style.
						 &n_width,     // @pyparm int|width||The pen width.
						 &cr_color)) { // @pyparm long|color||The pen color.
	return NULL;
  }
  lp.lopnStyle = n_pen_style;
  lp.lopnWidth.x = n_width;
  lp.lopnWidth.y = 0;
  lp.lopnColor = cr_color;

  CPen *pPen = new CPen;
  if (!pPen->CreatePenIndirect (&lp)) {
	delete pPen; // clean up on error.
	RETURN_ERR ("CreatePenIndirect call failed");
  }
  return ui_assoc_object::make (ui_pen_object::type, pPen);
}