static void MailPopupPreview(DWORD colorBack, DWORD colorText, TCHAR *title, TCHAR *emailInfo, int delay)
{
	POPUPDATAT ppd = { 0 };
	HICON hIcon = GetIcolibIcon(IDI_MAIL);
	ppd.lchIcon = CopyIcon(hIcon);
	ReleaseIcolibIcon(hIcon);
	_tcscpy(ppd.lptzContactName, title);
	_tcscpy(ppd.lptzText, emailInfo);
	ppd.colorBack = colorBack;
	ppd.colorText = colorText;
	ppd.iSeconds = delay;
	if ( ServiceExists(MS_POPUP_ADDPOPUPT))
		PUAddPopupT(&ppd);
}