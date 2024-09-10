BOOL AddinHelper::TodayNotDo(const wchar_t* szValueName)
{
	DWORD dwLastUTC = 0;
	BOOL bCando = FALSE;
	ATL::CRegKey key;
	if (key.Open(HKEY_CURRENT_USER, REGEDITPATH) == ERROR_SUCCESS) {
		bCando = TRUE;
		if(key.QueryDWORDValue(szValueName, dwLastUTC) == ERROR_SUCCESS) {
			__time64_t tTime = (__time64_t)dwLastUTC;
			tm* pTm = _localtime64(&tTime);
			LONG nLastDay = pTm->tm_mday;
			LONG nLastMonth = pTm->tm_mon;
			LONG nLastYear = pTm->tm_year;

			__time64_t lCurTime;
			_time64( &lCurTime); 
			tm* pTmc = _localtime64(&lCurTime);

			LONG nCurDay = pTmc->tm_mday;
			LONG nCurMonth = pTmc->tm_mon;
			LONG nCurYear = pTmc->tm_year;
			TSDEBUG4CXX("TodayHasDo check time pTmc = "<<nCurYear<<nCurMonth<<nCurDay<<", pTm = "<<nLastYear<<nLastMonth<<nLastDay);
			if (nCurDay == nLastDay && nCurMonth == nLastMonth && nCurYear == nLastYear){
				bCando = FALSE;
			}
			else{
				bCando = TRUE;
			}
		}
		key.Close();
	}
	return bCando;
}