void dialogEditor_dataitem::SetAddressState(BOOL bState)
{
	CEdit* pEdit = NULL;
	if((pEdit = (CEdit*)GetDlgItem(IDC_EDITOR_DATAITEM_ADDRESSHIGH)) == NULL)
		return;
	pEdit->EnableWindow(bState);
	CSpinButtonCtrl* pSpin = NULL;
	if((pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_EDITOR_DATAITEM_ADDRESSHIGHSPIN)) == NULL)
		return;
	pSpin->EnableWindow(bState);
}