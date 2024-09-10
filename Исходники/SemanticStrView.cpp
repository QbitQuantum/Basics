void CSemanticStrView::PasteClipboard() 
{
	OpenClipboard();
    HGLOBAL hMem = ::GetClipboardData(CF_UNICODETEXT );
    if (!hMem) {        
        CloseClipboard();        
        return;    
    }

	wchar_t s  [5000];
	if ( GlobalSize(hMem) > 4999) 
	{
		AfxMessageBox (" Text is too big!");
	};

	CopyMemory( s, hMem, GlobalSize(hMem));
	s[GlobalSize(hMem)] = 0;
    CString Q = s;
	char cmd[5200];
	strcpy (cmd, "$main.controls.mainEntry insert 0.0 \"");
    for (size_t i=0; i < Q.GetLength();i++)
		if (s[i] == '"')
			strcat (cmd, "\\\"");
		else
		{   size_t l = strlen(cmd);
			cmd[l] = Q[i];
			cmd[l+1] = 0; };

    strcat (cmd, "\"");
    if (Tcl_Eval(theInterp,cmd)!=0)
		AfxMessageBox ("Cannot set value");
	CloseClipboard();

}