static bool s_AskForMathMLPathname(XAP_Frame * pFrame,
					   char ** ppPathname)
{
	// raise the file-open dialog for inserting a MathML equation.
	// return a_OK or a_CANCEL depending on which button
	// the user hits.
	// return a pointer a g_strdup()'d string containing the
	// pathname the user entered -- ownership of this goes
	// to the caller (so free it when you're done with it).

	UT_DEBUGMSG(("s_AskForMathMLPathname: frame %p\n", pFrame));

	UT_return_val_if_fail (ppPathname, false);
	*ppPathname = NULL;

	pFrame->raise();

	XAP_DialogFactory * pDialogFactory
		= static_cast<XAP_DialogFactory *>(pFrame->getDialogFactory());

	XAP_Dialog_FileOpenSaveAs * pDialog
		= static_cast<XAP_Dialog_FileOpenSaveAs *>(pDialogFactory->requestDialog(XAP_DIALOG_ID_INSERTMATHML));
	UT_return_val_if_fail (pDialog, false);

	pDialog->setCurrentPathname(NULL);
	pDialog->setSuggestFilename(false);

	/* 
	TODO: add a "MathML (.xml)" entry to the file type list, and set is as the default file type

	pDialog->setFileTypeList(szDescList, szSuffixList, static_cast<const UT_sint32 *>(nTypeList));
	*/

	pDialog->runModal(pFrame);

	XAP_Dialog_FileOpenSaveAs::tAnswer ans = pDialog->getAnswer();
	bool bOK = (ans == XAP_Dialog_FileOpenSaveAs::a_OK);

	if (bOK)
	{
		const char * szResultPathname = pDialog->getPathname();
		UT_DEBUGMSG(("MATHML Path Name selected = %s \n",szResultPathname));
		if (szResultPathname && *szResultPathname)
			*ppPathname = g_strdup(szResultPathname);

		UT_sint32 type = pDialog->getFileType();

		// If the number is negative, it's a special type.
		// Some operating systems which depend solely on filename
		// suffixes to identify type (like Windows) will always
		// want auto-detection.
		if (type < 0)
		{
			switch (type)
			{
			case XAP_DIALOG_FILEOPENSAVEAS_FILE_TYPE_AUTO:
				// do some automagical detecting
				break;
			default:
				// it returned a type we don't know how to handle
				UT_ASSERT_HARMLESS(UT_SHOULD_NOT_HAPPEN);
			}
		}
		else
		{
			/* todo */
		}
	}

	pDialogFactory->releaseDialog(pDialog);

	return bOK;
}