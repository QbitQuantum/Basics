///
///	@brief	파일 첨부 DLG 제어
///
BOOL WINAPI GetOpenFileNameWCallback(
  _Inout_ LPOPENFILENAMEW lpofn
)
{
	_TRACE(L"");
	CString strURL = GetURL();
	BOOL bRet = FALSE;

	/// 파일 첨부 차단
	if(TRUE == pRule->IsBlockAttachFile())
	{
		/// 파일 첨부 허가 URL 검사
		if(TRUE == SearchStringFromFile(ALLOW_ATTACH_FILE_URL_TXT, strURL))
			bRet = GetOpenFileNameWNext(lpofn);
		else
		{
			AfxMessageBox(L"Mini-DLP에 의해 파일 첨부가 차단됩니다.");
			return FALSE;
		}
	}
	else
		bRet = GetOpenFileNameWNext(lpofn);

	/// 첨부 파일 로그를 남김
	if(TRUE == pRule->IsLoggingMail() && TRUE == pRule->IsLoggingAttachFile())
	{
		if(NULL != *lpofn->lpstrFile)
		{
			if(FALSE == PathIsDirectoryW(lpofn->lpstrFile))
				MakeLogFile(LOG_WEB_FILE, lpofn->lpstrFile);
			else
			{
				CStringArray strArr;
				/// 포인터 연산을 위해 저장
				LPCWSTR lpTemp = lpofn->lpstrFile;
				while(TRUE)
				{
					lpTemp += wcslen(lpTemp) + 1;
					if(NULL != *lpTemp)
						MakeLogFile(LOG_WEB_FILE,(CString)lpofn->lpstrFile + L"\\" + lpTemp);
					else
						break;
				}
			}
		}
	}

	return bRet;
};