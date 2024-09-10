// @pymethod |win32net|NetUserChangePassword|Changes the password for a user.
PyObject *PyNetUserChangePassword(PyObject *self, PyObject *args) 
{
	// @comm A server or domain can be configured to require that a
	// user log on to change the password on a user account.
	// If that is the case, you need administrator or account operator access
	// to change the password for another user acount.
	// If logging on is not required, you can change the password for
	// any user account, so long as you know the current password.
	WCHAR *szServer = NULL;
	WCHAR *szName = NULL;
	WCHAR *szOld = NULL;
	WCHAR *szNew = NULL;
	PyObject *obName, *obServer, *obOld, *obNew;
	PyObject *ret = NULL;
	DWORD err = 0;
	// @pyparm string/<o PyUnicode>|server||The name of the server, or None.
	// @pyparm string/<o PyUnicode>|username||The user name, or None for the current username.
	// @pyparm string/<o PyUnicode>|oldPassword||The old password
	// @pyparm string/<o PyUnicode>|newPassword||The new password
	if (!PyArg_ParseTuple(args, "OOOO", &obServer, &obName, &obOld, &obNew))
		return NULL;
	if (!PyWinObject_AsWCHAR(obServer, &szServer, TRUE))
		goto done;
	if (!PyWinObject_AsWCHAR(obName, &szName, TRUE))
		goto done;
	if (!PyWinObject_AsWCHAR(obOld, &szOld, FALSE))
		goto done;
	if (!PyWinObject_AsWCHAR(obNew, &szNew, FALSE))
		goto done;

	err = NetUserChangePassword(szServer, szName, szOld, szNew);
	if (err) {
		ReturnNetError("NetUserChangePassword",err);	// @pyseeapi NetUserChangePassword
		goto done;
	}
	ret = Py_None;
	Py_INCREF(Py_None);
done:
	PyWinObject_FreeWCHAR(szServer);
	PyWinObject_FreeWCHAR(szName);
	PyWinObject_FreeWCHAR(szOld);
	PyWinObject_FreeWCHAR(szNew);
	return ret;
}