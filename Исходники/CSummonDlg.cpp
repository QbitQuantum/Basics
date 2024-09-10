void CSummonDlg::SelectMP3(BOOL check)
{
	CButton *cBut;
	CComboBox *cBox;
	char i;

	cBut=(CButton *)GetDlgItem( IDC_RADIO_SUMMON_BITRATE);
	cBut->EnableWindow(check);
	cBut=(CButton *)GetDlgItem( IDC_RADIO1);
	cBut->EnableWindow(check);
	cBut=(CButton *)GetDlgItem( IDC_RADIO6);
	cBut->EnableWindow(check);

	cBox=(CComboBox *)GetDlgItem( IDC_COMBO_SUMMON_CBR);
	cBox->EnableWindow(check);
	cBox=(CComboBox *)GetDlgItem( IDC_COMBO_SUMMON_VBRMIN);
	cBox->EnableWindow(check);
	cBox=(CComboBox *)GetDlgItem( IDC_COMBO_SUMMON_VBRMAX);
	cBox->EnableWindow(check);
	
	cBox=(CComboBox *)GetDlgItem( IDC_COMBO_SUMMON_VBRQUALITY);
	cBox->EnableWindow(check);
	cBox->ResetContent();
	for(i='0';i<='9';i++)
	{	
		cBox->AddString((LPCTSTR)i);
	}
	cBox->SetCurSel(4);

	cBox=(CComboBox *)GetDlgItem( IDC_COMBO_SUMMON_SAMPLERATE);
	cBox->EnableWindow(check);
	cBox=(CComboBox *)GetDlgItem( IDC_COMBO_SUMMON_OUTPUT_MPEG_VERSION);
	cBox->EnableWindow(check);
	cBox->ResetContent();
	cBox->AddString((LPCTSTR)"MPEG2");
	cBox->AddString((LPCTSTR)"MPEG1");
	cBox->SetCurSel(1);

}