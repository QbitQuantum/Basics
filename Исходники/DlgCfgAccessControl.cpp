void CDlgCfgAccessControl::StuToDlg()
{
	// door open method
	m_cmbOpenMethod.SetCurSel((CFG_DOOR_OPEN_METHOD)m_stuInfo.emDoorOpenMethod);
	
	// door unlock hold time
	SetDlgItemInt(IDC_ACCESSCONTROL_EDT_UNLOCKHOLD, m_stuInfo.nUnlockHoldInterval);
	
	// door close timeout
	SetDlgItemInt(IDC_ACCESSCONTROL_EDT_CLOSETIMEOUT, m_stuInfo.nCloseTimeout);
	
	// open time index in config of AccessTimeSchedule, start from 0
	m_cmbOpenTimeIndex.SetCurSel(m_stuInfo.nOpenAlwaysTimeIndex);
	
	// holiday record set recNo
	SetDlgItemInt(IDC_ACCESSCONTROL_EDT_HOLIDAYTIMERECNO, m_stuInfo.nHolidayTimeRecoNo);
	
	// break in alarm enable
	if (m_stuInfo.bBreakInAlarmEnable)
	{
		m_chkBreakAlarm.SetCheck(BST_CHECKED);
	}
	else
	{
		m_chkBreakAlarm.SetCheck(BST_UNCHECKED);
	}
	
	// repeat enter alarm enable
	if (m_stuInfo.bRepeatEnterAlarm)
	{
		m_chkRepeatEnterAlarm.SetCheck(BST_CHECKED);
	}
	else
	{
		m_chkRepeatEnterAlarm.SetCheck(BST_UNCHECKED);
	}
	
	// door not close enable
	if (m_stuInfo.bDoorNotClosedAlarmEnable)
	{
		m_chkDoorNotCloseAlarm.SetCheck(BST_CHECKED);
	}
	else
	{
		m_chkDoorNotCloseAlarm.SetCheck(BST_UNCHECKED);
	}
	
	// duress alarm enable
	if (m_stuInfo.bDuressAlarmEnable)
	{
		m_chkDuressAlarm.SetCheck(BST_CHECKED);
	}
	else
	{
		m_chkDuressAlarm.SetCheck(BST_UNCHECKED);
	}
	
	// sensor alarm enable
	if (m_stuInfo.bSensorEnable)
	{
		m_chkSensor.SetCheck(BST_CHECKED);
	}
	else
	{
		m_chkSensor.SetCheck(BST_UNCHECKED);
	}
	
	// time section...

}