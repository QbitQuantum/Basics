BOOL CValueList::SetComboBoxValue(CComboBox &cb, int nValue, BOOL bDisableOnNoMatch)
{
	CValueItem vi;

	int nCount = cb.GetCount();
	for (int i=0;i<nCount;i++)
		if ((int)cb.GetItemData(i) == nValue)
		{
			cb.SetCurSel(i);
			if (bDisableOnNoMatch)
				cb.EnableWindow(TRUE);
			return(TRUE);
		}

	cb.SetCurSel(-1);
	if (bDisableOnNoMatch)
		cb.EnableWindow(FALSE);
	return(FALSE);

	cb.SetCurSel(-1);
	if (bDisableOnNoMatch)
		cb.EnableWindow(FALSE);
	return(FALSE);
}