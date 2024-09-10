void AP_Win32Dialog_Paragraph::runModal(XAP_Frame * pFrame)
{
	/*
	  This dialog is non-persistent.

	  This dialog should do the following:

	  - Construct itself to represent the paragraph properties
	    in the base class (AP_Dialog_Paragraph).

		The Unix one looks just like Microsoft Word 97's Paragraph
		dialog.

	  - The base class stores all the paragraph parameters in
	    m_paragraphData.

	  On "OK" (or during user-interaction) the dialog should:

	  - Save all the data to the m_paragraphData struct so it
	    can be queried by the caller (edit methods routines).

	  On "Cancel" the dialog should:

	  - Just quit, the data items will be ignored by the caller.

	  On "Tabs..." the dialog should (?):

	  - Just quit, discarding changed data, and let the caller (edit methods)
	    invoke the Tabs dialog.

	*/

	// store frame for later use
	m_pFrame = pFrame;

	// raise the dialog
	XAP_Win32App * pWin32App = static_cast<XAP_Win32App *>(m_pApp);

	XAP_Win32LabelledSeparator_RegisterClass(pWin32App);	

//	createModal(pFrame, MAKEINTRESOURCEW(AP_RID_DIALOG_PARAGRAPH));

	LPCWSTR lpTemplate = NULL;

	UT_ASSERT(m_id == AP_DIALOG_ID_PARAGRAPH);

	lpTemplate = MAKEINTRESOURCEW(AP_RID_DIALOG_PARAGRAPH);

	XAP_Win32FrameImpl* pWin32FrameImpl = static_cast<XAP_Win32FrameImpl*>(pFrame->getFrameImpl());

	HWND hFrameWnd = pWin32FrameImpl->getTopLevelWindow();

	int result = DialogBoxParamW(pWin32App->getInstance(),lpTemplate,
								hFrameWnd,
								(DLGPROC)s_dlgProc,(LPARAM)this);
	UT_ASSERT((result != -1));
}