void CEnvelopeTypeDialog::UpdatePreview(void)
{
	CWnd* pPreview = GetDlgItem(IDC_MAKE_PREVIEW);
	if (pPreview != NULL)
	{
		pPreview->InvalidateRect(NULL);
	}
}