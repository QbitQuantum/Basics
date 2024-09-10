void CTabToolsDlg::OnBnClickedBtnStopSe()
{
	TerminateThread(this->_opThds, 0);
	_fcloseall();
	this->_SetItemStatusInList(this->_curErasingItem, _T("Canceled"));
	this->_EnableCtrls(1);
}