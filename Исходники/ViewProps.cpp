bool CViewProps::OnButtonGUID(CButton* Button, CPLPropertyEditEx *Prop, CPLCategory *Cat)
{
	if(!m_View) return false;
	CProjectDoc* Doc = m_View->GetDocument();
	if(!Doc || !Doc->Game) return false;

	CGuidDlg dlg;
	dlg.m_Guid = Doc->m_Settings->m_GameGUID;
	if(dlg.DoModal()==IDOK)
	{
		Doc->m_Settings->m_GameGUID = dlg.m_Guid;

		CString str;
		LPOLESTR  olestr;
		StringFromIID(Doc->m_Settings->m_GameGUID, &olestr);
		str = CString(olestr);
		CoTaskMemFree(olestr);

		Prop->SetValue(str);
		m_PropList.Redraw();
	}

	return false;
}