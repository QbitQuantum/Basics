/*
 * External interface
 */
static void
DoPyCommand(const char *cmd, rangeinitializer init_range, runner run, void *arg)
{
#if defined(MACOS) && !defined(MACOS_X_UNIX)
	GrafPtr		oldPort;
#endif
#if defined(HAVE_LOCALE_H) || defined(X_LOCALE)
	char		*saved_locale;
#endif
	PyObject		*cmdstr;
	PyObject		*cmdbytes;
	PyGILState_STATE	pygilstate;

#if defined(MACOS) && !defined(MACOS_X_UNIX)
	GetPort(&oldPort);
	/* Check if the Python library is available */
	if ((Ptr)PyMac_Initialize == (Ptr)kUnresolvedCFragSymbolAddress)
		goto theend;
#endif
	if (Python3_Init())
		goto theend;

	init_range(arg);

	Python_Release_Vim();	    /* leave vim */

#if defined(HAVE_LOCALE_H) || defined(X_LOCALE)
	/* Python only works properly when the LC_NUMERIC locale is "C". */
	saved_locale = setlocale(LC_NUMERIC, NULL);
	if (saved_locale == NULL || STRCMP(saved_locale, "C") == 0)
		saved_locale = NULL;
	else {
		/* Need to make a copy, value may change when setting new locale. */
		saved_locale = (char *)vim_strsave((char_u *)saved_locale);
		(void)setlocale(LC_NUMERIC, "C");
	}
#endif

	pygilstate = PyGILState_Ensure();

	/* PyRun_SimpleString expects a UTF-8 string. Wrong encoding may cause
	 * SyntaxError (unicode error). */
	cmdstr = PyUnicode_Decode(cmd, strlen(cmd),
							  (char *)ENC_OPT, CODEC_ERROR_HANDLER);
	cmdbytes = PyUnicode_AsEncodedString(cmdstr, "utf-8", CODEC_ERROR_HANDLER);
	Py_XDECREF(cmdstr);

	run(PyBytes_AsString(cmdbytes), arg, &pygilstate);
	Py_XDECREF(cmdbytes);

	PyGILState_Release(pygilstate);

#if defined(HAVE_LOCALE_H) || defined(X_LOCALE)
	if (saved_locale != NULL) {
		(void)setlocale(LC_NUMERIC, saved_locale);
		vim_free(saved_locale);
	}
#endif

	Python_Lock_Vim();		    /* enter vim */
	PythonIO_Flush();
#if defined(MACOS) && !defined(MACOS_X_UNIX)
	SetPort(oldPort);
#endif

theend:
	return;	    /* keeps lint happy */
}