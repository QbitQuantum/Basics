void CPIDCreateDlg::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	pids.clear();

	for (int row = 1; row < m_cPidTable.GetRowCount(); ++row) {
		CString startTemp = m_cPidTable.GetItemText(row, 1);
		CString targetTemp = m_cPidTable.GetItemText(row, 2);
		CString kp = m_cPidTable.GetItemText(row, 3);
		CString kd = m_cPidTable.GetItemText(row, 4);
		CString ki = m_cPidTable.GetItemText(row, 5);

		pids.push_back( PID( _wtof(startTemp), _wtof(targetTemp), _wtof(kp), _wtof(kd), _wtof(ki) ) );
	}

	*pResult = 0;
}