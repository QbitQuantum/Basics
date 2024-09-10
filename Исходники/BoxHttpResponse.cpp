void CBoxHttpResponse::put_ExpiresAbsolute(DATE dateExpires)
{
	SYSTEMTIME st;
	CString strTime;

	VariantTimeToSystemTime(dateExpires, &st);
	TimeToString(st, strTime);

	m_pAccept->SetHeader(_T("Expires"), strTime);
}