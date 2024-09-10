void CModulePropertiesDlg::OnCbnSelchangeExpansion()
{
	CComboBox *pExpansionChipBox = static_cast<CComboBox*>(GetDlgItem(IDC_EXPANSION));
	CSliderCtrl *pSlider = static_cast<CSliderCtrl*>(GetDlgItem(IDC_CHANNELS));

	// Expansion chip
	unsigned int iExpansionChip = theApp.GetChannelMap()->GetChipIdent(pExpansionChipBox->GetCurSel());

	CString channelsStr;
	channelsStr.LoadString(IDS_PROPERTIES_CHANNELS);
	if (iExpansionChip == SNDCHIP_N163) {
		pSlider->EnableWindow(TRUE);
		int Channels = m_pDocument->GetNamcoChannels();
		pSlider->SetPos(Channels);
		channelsStr.AppendFormat(_T(" %i"), Channels);
	}
	else {
		pSlider->EnableWindow(FALSE);
		channelsStr.Append(_T(" N/A"));
	}
	SetDlgItemText(IDC_CHANNELS_NR, channelsStr);
}