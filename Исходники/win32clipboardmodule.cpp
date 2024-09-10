static PyObject *
py_get_open_clipboard_window(PyObject* self, PyObject* args)
{

  CHECK_NO_ARGS2(args, "GetOpenClipboardWindow");

  HWND rc;
  Py_BEGIN_ALLOW_THREADS;
  rc = GetOpenClipboardWindow();
  Py_END_ALLOW_THREADS;

  if (!rc)
    return ReturnAPIError("GetOpenClipboardWindow");

  return PyWinLong_FromHANDLE(rc);

  // @comm If an application or dynamic-link library (DLL) specifies a NULL
  // window handle when calling the OpenClipboard function, the clipboard is
  // opened but is not associated with a window. In such a case,
  // GetOpenClipboardWindow returns NULL. 

  // @pyseeapi GetOpenClipboardWindow

  // @rdesc If the function succeeds, the return value is the handle of the
  // window that has the clipboard open. 
  // If the function fails, win32api.error is raised with the GetLastError
  // info.

}