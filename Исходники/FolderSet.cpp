void CFolderSet::UpdatePackSet()
{
	CButton* pPack = (CButton*)GetDlgItem(IDC_RADIO_PACK);
	CButton* pUnPack = (CButton*)GetDlgItem(IDC_RADIO_UNPACK);
	CComboBox* pComboPack = (CComboBox*)GetDlgItem(IDC_COMBO_PACKAGE_TYPE);	
	if(pPack == NULL || pUnPack == NULL || pComboPack == NULL)	return;

	CButton* pCompress = (CButton*)GetDlgItem(IDC_RADIO_COMPRESS);
	CButton* pUnCompress = (CButton*)GetDlgItem(IDC_RADIO_UNCOMPRESS);
	CComboBox* pComboCompress= (CComboBox*)GetDlgItem(IDC_COMBO_COMPRESS_TYPE);
	if(pCompress == NULL || pUnCompress == NULL || pComboCompress == NULL)	return;

	if( (m_nPackType & 0x1) == 1)
	{
		pPack->SetCheck(BST_UNCHECKED);
		pUnPack->SetCheck(BST_CHECKED);
		pComboPack->EnableWindow(false);
		pComboPack->SetCurSel(-1);
		//设置为不压缩
		pCompress->SetCheck(BST_UNCHECKED);
		pCompress->EnableWindow(false);
		pUnCompress->SetCheck(BST_CHECKED);
		pComboCompress->EnableWindow(false);
	}
	else
	{
		pPack->SetCheck(BST_CHECKED);
		pUnPack->SetCheck(BST_UNCHECKED);
		pComboPack->EnableWindow(true);
		int nPos = GetComcoPackPosByID(m_nPackType);
		pComboPack->SetCurSel(nPos);

		//设置为不压缩
		pCompress->EnableWindow(true);
		pComboCompress->EnableWindow(true);
	}
}