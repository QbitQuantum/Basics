void CAddVariableDlg::validate_data(int set_focus) {
	CString temp_data;

	CEdit *edit = (CEdit *) GetDlgItem(IDC_ADD_VARIABLE_DEFAULT_VALUE);
	edit->GetWindowText(temp_data);

	// check for 0 string length
	if (strlen(temp_data) == 0) { //-V805
		m_data_validated = false;
	} else {
		if (m_type_number) {
			// verify valid number
			int temp_num = atoi(temp_data);
			char buf[TOKEN_LENGTH];
			sprintf(buf, "%d", temp_num);

			if (stricmp(buf, temp_data)) {
				m_data_validated = false;
			} else {
				m_data_validated = true;
			}
		} else {
			m_data_validated = true;
		}
	}

	// Display message and reset focus
	if ((!m_data_validated) && (set_focus == RESET_FOCUS)) {
		MessageBox("Invalid Default Value.");
		edit->SetFocus();
		edit->SetSel(0, -1);
	}
}