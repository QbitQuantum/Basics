void CMixereView::LoadAudio()
{
	CFileDialog	fd(TRUE, ".wav", NULL,
		OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		CChannel::GetFileFilter());
	// prepare OPENFILENAME struct for multiple select
	CString	Buffer;
	const	BUFSIZE = 0x7fff;
	LPTSTR	FileBuf = Buffer.GetBufferSetLength(BUFSIZE);
	ZeroMemory(FileBuf, BUFSIZE);
	fd.m_ofn.lpstrFile = FileBuf;
	fd.m_ofn.nMaxFile = BUFSIZE;
	fd.m_ofn.nFileOffset = 0;
	CString	Title(LDS(LOAD_AUDIO));
	fd.m_ofn.lpstrTitle = Title;
	// display the dialog
	int	retc = fd.DoModal();
	int	Pos = m_CurPos;
	if (retc == IDOK) {
		// iterate through the results
		CStringArray	ErrPath;
		POSITION	FilePos;
        FilePos = fd.GetStartPosition();
        while (FilePos != NULL) {
			CString	Path = fd.GetNextPathName(FilePos);
			if (!LoadAudio(Pos++, Path))
				AddStringUnique(ErrPath, Path);
		}
		// if audio files couldn't be opened, display error message
		if (ErrPath.GetSize())
			MsgBoxStrList(LDS(CANT_LOAD_AUDIO), ErrPath);
	} else {
		if (CommDlgExtendedError())
			AfxMessageBox(LDS(FILE_DIALOG_ERROR));
	}
}