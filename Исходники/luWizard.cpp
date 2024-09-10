	virtual bool TransferDataFromWindow()
    {
		wxFileName fileName = m_filePicker->GetFileName();
		if (fileName.FileExists())
		{
			alertDlg("Project file is already exist.\nSelect other filename.", this);
			m_filePicker->SetFocus();
			return false;
		}

		if (!fileName.IsOk())
		{
			alertDlg("Project file name is empty or invalid.", this);
			m_filePicker->SetFocus();
			return false;
		}

		if (m_textName->GetLabelText().IsEmpty())
		{
			alertDlg("Project name is empty.", this);
			m_textName->SetFocus();
			return false;
		}

		return true;
	}