int DoMyControlProcessing(HWND hdlg,UINT message,WPARAM wParam,LPARAM lParam,INT_PTR *bReturn)
{
	switch(message) {
		case WM_INITDIALOG:
			EnumChildWindows(hdlg,MyControlsEnumChildren,0);
			if(hEmfHeaderLogo==NULL) {
				HRSRC hRsrc=FindResourceA(hInst,MAKEINTRESOURCEA(IDE_HDRLOGO),"EMF");
				HGLOBAL hGlob=LoadResource(hInst,hRsrc);
				hEmfHeaderLogo=SetEnhMetaFileBits(SizeofResource(hInst,hRsrc),(PBYTE)LockResource(hGlob));
			}
			SendDlgItemMessage(hdlg,IDC_HDRLOGO,STM_SETIMAGE,IMAGE_ENHMETAFILE,(LPARAM)hEmfHeaderLogo);
			break;
		case WM_CTLCOLORSTATIC:
			if((GetWindowLong((HWND)lParam,GWL_STYLE)&0xFFFF)==0) {
				char szText[256];
				GetWindowTextA((HWND)lParam,szText,sizeof(szText));
				if(!strcmp(szText,"whiterect")) {
					SetTextColor((HDC)wParam,RGB(255,255,255));
					SetBkColor((HDC)wParam,RGB(255,255,255));
					SetBkMode((HDC)wParam,OPAQUE);
					*bReturn=(INT_PTR)GetStockObject(WHITE_BRUSH);
					return TRUE;
				}
				else {
					SetBkMode((HDC)wParam,TRANSPARENT);
					*bReturn=(INT_PTR)GetStockObject(NULL_BRUSH);
					return TRUE;
				}
			}
			break;
	}
	return FALSE;
}