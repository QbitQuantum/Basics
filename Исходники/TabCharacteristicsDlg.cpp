BOOL CTabCharacteristicsDlg::SetValue(int nValue, CComboBox &cb)
{
	int nCount = cb.GetCount();
	for (int i=0;i<nCount;i++)
		if ((int)cb.GetItemData(i) == nValue)
		{
			cb.SetCurSel(i);
			cb.EnableWindow(TRUE);
			return(TRUE);
		}

	cb.SetCurSel(-1);
	cb.EnableWindow(FALSE);
	return(FALSE);
}