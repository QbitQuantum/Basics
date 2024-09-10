void CPhotoProjectsTypeDlg::UpdatePreview(void)
{
	CWnd* pPreview = GetDlgItem(IDC_PREVIEW);
	if (pPreview != NULL)
	{
		pPreview->InvalidateRect(NULL);
	}
}