// enum camera callback
static void callback(void *pItem, char *pDeviceName)
{
	TCHAR buffer[80] = L"";
	size_t wlen;
	int *idcCam = (int*)pItem;
	if (*idcCam <= IDC_CAM4) {
		CButton *item = (CButton*)pDlg->GetDlgItem(*idcCam);

		item->EnableWindow();
		item->SetCheck(BST_CHECKED);
		item->ShowWindow(SW_SHOWNORMAL);
		mbstowcs_s(&wlen, buffer, pDeviceName, 80);
		// Buffaloのカメラの行末にCR,LFが入っているので、これを除去
		for (wlen--; 0 < wlen; wlen--) {
			if (buffer[wlen] == 13 || buffer[wlen] == 10)
				buffer[wlen] = 0;
		}
		item->SetWindowText(buffer);
	}
	(*idcCam)++;
}