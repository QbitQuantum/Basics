void CPPgScheduler::OnDisableTime2() {
	GetDlgItem(IDC_DATETIMEPICKER2)->EnableWindow( IsDlgButtonChecked(IDC_CHECKNOENDTIME)==0 );
}