void CCtrlDialog::OnBnClickedMfcbuttonFaceident()
{
	CFaceIdentification faceIdent(m_pAsmbBody);
	faceIdent.FaceIdentify();
	this->SetTreeItems(m_pAsmbBody);

	// Invalidate button state
	CWnd *pWnd = GetDlgItem(IDC_MFCBUTTON_FACEIDENT);
	pWnd->EnableWindow(FALSE);
	pWnd = GetDlgItem(IDC_MFCBUTTON_CUT);
	pWnd->EnableWindow(TRUE);
}