void CProcessingOptions::OnClickedRadioEntireImage()
{
	CEdit * ctrlEditCoverage = reinterpret_cast<CEdit *> (GetDlgItem(IDC_PERCENT_COVERAGE));
	ctrlEditCoverage->EnableWindow(FALSE);
}