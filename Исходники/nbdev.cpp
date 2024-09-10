CString CNBUnitDevice::GetIDString(TCHAR HiddenChar)
{
	CString strText;
	if (m_pDevice) {
		CString strID = m_pDevice->m_BaseInfo.szDeviceStringId;
		strID.Remove(_T('-'));

		strText += 
			strID.Mid(0, 5) + _T("-") +
			strID.Mid(5, 5) + _T("-") +
			strID.Mid(10, 5) + _T("-");
		strText += HiddenChar;
		strText += HiddenChar;
		strText += HiddenChar;
		strText += HiddenChar;
		strText += HiddenChar;
		//		strID.Mid(0, 5) + _T("-") +
	} else {
		//
		// to do: create ID from device ID.(But we don't have corresponding NDAS device object!!)

		//
		strText += "";
	}
	return strText;
}