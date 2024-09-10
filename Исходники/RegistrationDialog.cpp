BOOL CreditsDialog::OnInitDialog()
{
	char legalFilePath[MAX_PATH];
	strcpy_s(legalFilePath, sizeof(legalFilePath), getCormanLispDirectory());
	strcat_s(legalFilePath, sizeof(legalFilePath), "\\documentation\\credits.txt");
	DWORD length;
	mappedFile = MapFile(legalFilePath, &length);
	char buf[0x6000];
	if (mappedFile)
		memcpy(buf, mappedFile, length);
	buf[length] = 0;
	CWnd* item = GetDlgItem(IDC_LEGALTEXT);
	if (item && mappedFile)
		item->SetWindowText(buf);

	CDC* cdc = item->GetDC();
	HDC hDC = cdc->m_hDC;
	CFont* font = theApp.getCourierFont(hDC, 10);
	item->SetFont(font, TRUE);
	SelectObject(hDC, *font);

	item = GetDlgItem(IDOK);
	if (item)
		((CButton*)item)->SetButtonStyle(BS_DEFPUSHBUTTON);
	SetDefID(IDOK);
	return FALSE;
}