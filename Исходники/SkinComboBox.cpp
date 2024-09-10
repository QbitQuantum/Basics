void CSkinComboBox::PreSubclassWindow()
{
	//变量定义
	COMBOBOXINFO ComboBoxInfo;
	ComboBoxInfo.cbSize=sizeof(ComboBoxInfo);

	//绑定控件
	if (GetComboBoxInfo(&ComboBoxInfo)==TRUE)
	{
		if (ComboBoxInfo.hwndItem!=NULL) 
		{
			m_SkinComboBoxEdit.SetOwnerWnd(GetSafeHwnd());
			m_SkinComboBoxEdit.SubclassWindow(ComboBoxInfo.hwndItem);
		}

		if (ComboBoxInfo.hwndList!=NULL) 
		{
			m_SkinComboBoxList.SetOwnerWnd(GetSafeHwnd());
			m_SkinComboBoxList.SubclassWindow(ComboBoxInfo.hwndList);
		}
	}

	CComboBox::PreSubclassWindow();
}