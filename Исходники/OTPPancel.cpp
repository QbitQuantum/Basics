void COTPPancel::OnChangeEditImei2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	strcpy(gIMEI2.szIMEI2,m_IMEI2.GetBuffer(0));
	if (15 == m_IMEI2.GetLength())
	{
		strncpy(gIMEI2.szIMEI2,m_IMEI2.GetBuffer(0), 14);
		gIMEI2.szIMEI2[14]='\0';
		GetNextDlgTabItem(GetFocus())->SetFocus();
	}
}