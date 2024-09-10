void CPageDisk::SetDlgItemInt64(int nID, __int64 nValue, BOOL bSigned, int nRadix) 
{
	CString dlgCString;
	LPSTR lpString = dlgCString.GetBuffer(32); // preallocate enough space
	unsigned __int64 unValue = (unsigned __int64) nValue; // setup an unsigned version

	if (bSigned)
		_i64toa(nValue, lpString, nRadix);
	else
		_ui64toa(unValue, lpString, nRadix);
	
	SetDlgItemText(nID, lpString);
	dlgCString.ReleaseBuffer();
}