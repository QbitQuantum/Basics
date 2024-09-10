bool CAdoRecordset::GetValue(char* strFieldName, tm& time, bool &nIsNull)
{
	_variant_t vt;
	bool rtn= GetValue(strFieldName,vt,nIsNull);
	if(vt.vt == VT_NULL || vt.vt == VT_EMPTY)  
	{
		nIsNull = true;
		return true;
	}

	SYSTEMTIME dt;
	VariantTimeToSystemTime(vt.date, &dt);
	time.tm_year = dt.wYear;
	time.tm_mon = dt.wMonth;
	time.tm_mday = dt.wDay;
	time.tm_hour = dt.wHour;
	time.tm_min = dt.wMinute;
	time.tm_sec = dt.wSecond;
	time.tm_isdst = dt.wMilliseconds;
	return rtn;	
}