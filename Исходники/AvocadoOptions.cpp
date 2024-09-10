void COptionsDlg::ClearCurrentPage ()
{
	CWnd * parentGroupBox = GetDlgItem (IDC_OPTIONGROUP);
	for (size_t i=0;i<m_currentPageControls.size ();i++)
	{
		CWnd *item = parentGroupBox->GetDlgItem  ( ((CWnd*)(m_currentPageControls[i].first))->GetDlgCtrlID ());
		if (item)
		{				
				if (m_currentPageControls[i].second.UIType == avocado::AvocadoOption::CHECKBOX)
				{
					CButton *obj = (CButton*)(m_currentPageControls[i].first);
					
				    bool ischek = (obj->GetCheck () > 0);

					m_currentPageControls[i].second.valueBool = ischek;

					item->DestroyWindow ();
					
					delete obj;
				}
				else if (m_currentPageControls[i].second.UIType == avocado::AvocadoOption::EDITBOX)
				{
					 int labelID = ((CWnd*)(m_currentPageControls[i].first))->GetDlgCtrlID () - 1100 + 2200;

					CWnd *labelitem = parentGroupBox->GetDlgItem  (labelID);
					
					if (labelitem)
					{
						labelitem->DestroyWindow ();
						CStatic *css = (CStatic*) labelitem;
						delete css;
					}
					CEdit *obj = (CEdit*)(m_currentPageControls[i].first);

					wchar_t buf[MAX_PATH];
					obj->GetWindowTextW (buf, MAX_PATH);
					char cbuf [MAX_PATH];
					::wcstombs (cbuf,buf,MAX_PATH);
					
					if (m_currentPageControls[i].second.Type == avocado::AvocadoOption::STRING)
						m_currentPageControls[i].second.valueString = string (cbuf);
					else if (m_currentPageControls[i].second.Type == avocado::AvocadoOption::FLOAT)
					{
						stringstream ss ( cbuf);
						ss >> m_currentPageControls[i].second.valueFloat;
					}
					else if (m_currentPageControls[i].second.Type == avocado::AvocadoOption::BOOL)
					{
						string ss ( cbuf);
						bool bv = false;
						if (ss == "Yes")
							bv = true; else bv = false;
						m_currentPageControls[i].second.valueBool = bv;
					}
					else if (m_currentPageControls[i].second.Type == avocado::AvocadoOption::INT)
					{
						stringstream ss ( cbuf);
						ss >> m_currentPageControls[i].second.valueInt;
					}