int
TkSelGetSelection(
    Tcl_Interp *interp,		/* Interpreter to use for reporting errors. */
    Tk_Window tkwin,		/* Window on whose behalf to retrieve the
				 * selection (determines display from which to
				 * retrieve). */
    Atom selection,		/* Selection to retrieve. */
    Atom target,		/* Desired form in which selection is to be
				 * returned. */
    Tk_GetSelProc *proc,	/* Procedure to call to process the selection,
				 * once it has been retrieved. */
    ClientData clientData)	/* Arbitrary value to pass to proc. */
{
    char *data, *destPtr;
    Tcl_DString ds;
    HGLOBAL handle;
    Tcl_Encoding encoding;
    int result, locale;

    if ((selection != Tk_InternAtom(tkwin, "CLIPBOARD"))
	    || (target != XA_STRING)
	    || !OpenClipboard(NULL)) {
	goto error;
    }

    /*
     * Attempt to get the data in Unicode form if available as this is less
     * work that CF_TEXT.
     */

    result = TCL_ERROR;
    if (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
	handle = GetClipboardData(CF_UNICODETEXT);
	if (!handle) {
	    CloseClipboard();
	    goto error;
	}
	data = GlobalLock(handle);
	Tcl_DStringInit(&ds);
	Tcl_UniCharToUtfDString((Tcl_UniChar *)data,
		Tcl_UniCharLen((Tcl_UniChar *)data), &ds);
	GlobalUnlock(handle);
    } else if (IsClipboardFormatAvailable(CF_TEXT)) {
	/*
	 * Determine the encoding to use to convert this text.
	 */

	if (IsClipboardFormatAvailable(CF_LOCALE)) {
	    handle = GetClipboardData(CF_LOCALE);
	    if (!handle) {
		CloseClipboard();
		goto error;
	    }

	    /*
	     * Get the locale identifier, determine the proper code page to
	     * use, and find the corresponding encoding.
	     */

	    Tcl_DStringInit(&ds);
	    Tcl_DStringAppend(&ds, "cp######", -1);
	    data = GlobalLock(handle);

	    /*
	     * Even though the documentation claims that GetLocaleInfo expects
	     * an LCID, on Windows 9x it really seems to expect a LanguageID.
	     */

	    locale = LANGIDFROMLCID(*((int*)data));
	    GetLocaleInfoA(locale, LOCALE_IDEFAULTANSICODEPAGE,
		    Tcl_DStringValue(&ds)+2, Tcl_DStringLength(&ds)-2);
	    GlobalUnlock(handle);

	    encoding = Tcl_GetEncoding(NULL, Tcl_DStringValue(&ds));
	    Tcl_DStringFree(&ds);
	} else {
	    encoding = NULL;
	}

	/*
	 * Fetch the text and convert it to UTF.
	 */

	handle = GetClipboardData(CF_TEXT);
	if (!handle) {
	    if (encoding) {
		Tcl_FreeEncoding(encoding);
	    }
	    CloseClipboard();
	    goto error;
	}
	data = GlobalLock(handle);
	Tcl_ExternalToUtfDString(encoding, data, -1, &ds);
	GlobalUnlock(handle);
	if (encoding) {
	    Tcl_FreeEncoding(encoding);
	}

    } else {
	CloseClipboard();
	goto error;
    }

    /*
     * Translate CR/LF to LF.
     */

    data = destPtr = Tcl_DStringValue(&ds);
    while (*data) {
	if (data[0] == '\r' && data[1] == '\n') {
	    data++;
	} else {
	    *destPtr++ = *data++;
	}
    }
    *destPtr = '\0';

    /*
     * Pass the data off to the selection procedure.
     */

    result = proc(clientData, interp, Tcl_DStringValue(&ds));
    Tcl_DStringFree(&ds);
    CloseClipboard();
    return result;

  error:
    Tcl_SetObjResult(interp, Tcl_ObjPrintf(
	    "%s selection doesn't exist or form \"%s\" not defined",
	    Tk_GetAtomName(tkwin, selection), Tk_GetAtomName(tkwin, target)));
    Tcl_SetErrorCode(interp, "TK", "SELECTION", "EXISTS", NULL);
    return TCL_ERROR;
}