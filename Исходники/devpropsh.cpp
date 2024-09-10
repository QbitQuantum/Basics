void
CDeviceAddWriteKeyDlg::OnWriteKeyChange(UINT /*wNotifyCode*/, int /*wID*/, HWND hWndCtl)
{
	CEdit wndWriteKey = hWndCtl;

	wndWriteKey.GetWindowText(
		m_strWriteKey.GetBuffer(NDAS_DEVICE_WRITE_KEY_LEN + 1),
		NDAS_DEVICE_WRITE_KEY_LEN + 1);

	m_strWriteKey.ReleaseBuffer();

	CButton wndOK = GetDlgItem(IDOK);
	if (m_strWriteKey.GetLength() == 5) 
	{
		BOOL fValid = ::NdasValidateStringIdKey(
			m_strDeviceId, 
			m_strWriteKey);
		wndOK.EnableWindow(fValid);
	}
	else 
	{
		wndOK.EnableWindow(FALSE);
	}

	SetMsgHandled(FALSE);
}