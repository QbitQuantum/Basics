void ALERT::OnClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	CListCtrl *pListctrl = (CListCtrl *)GetDlgItem(IDC_LIST1);
	if (pListctrl->GetItemText(pNMItemActivate->iItem, 0) == "1") {
		((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(TRUE);
	} else ((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(FALSE);
	SetDlgItemTextA(IDC_EDIT1, pListctrl->GetItemText(pNMItemActivate->iItem, 1));
	SetDlgItemTextA(IDC_EDIT2, pListctrl->GetItemText(pNMItemActivate->iItem, 2));
	SetDlgItemTextA(IDC_EDIT3, pListctrl->GetItemText(pNMItemActivate->iItem, 3));
	SetDlgItemTextA(IDC_EDIT5, pListctrl->GetItemText(pNMItemActivate->iItem, 4));

	*pResult = 0;
}