// CStrgDoc commands
void CStrgDoc::GetUserNameBek(CString &strNT, CString &strSQL)
{
	CString strCmp;
	CString strUsr;

	GetUserNameW((LPWSTR)m_UserName,&max);
//AfxMessageBox((LPWSTR)m_UserName);
	strUsr = (LPWSTR)m_UserName;
//	strUsr = strUsr.Left(13);

/*	GetComputerName(m_CompName,&max);
	strCmp=m_CompName;
	strCmp = strCmp.Left(11);
*/
	strNT = strUsr;
/*
	strNT+= _T("_");
	strNT+= strCmp;
*/
//---------------------------------
//AfxMessageBox(strNT);
/*	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(1, 0);
	int err = WSAStartup(wVersionRequested, &wsaData);
	if(err == 0)
	  {
		char hn[1024];
		if(gethostname((char *)&hn, 1024))
		  {
			int err = WSAGetLastError();
			MessageBeep(MB_OK);
		  };
		strNT+=_T("_");
		strCmp=hn;
		strCmp=strCmp.Left(11);
		strNT+=strCmp;
AfxMessageBox(strNT);
	  }
*/
//	AfxMessageBox(m_strNameNT);
/*	if (m_db.IsOpen()) {
		::SQLGetInfo(m_db.m_hdbc,SQL_USER_NAME,(PTR)m_UserName,(short) max,&cbData);
	}
	strSQL=m_UserName;
	*/
//	AfxMessageBox(m_strNameSQL);

}