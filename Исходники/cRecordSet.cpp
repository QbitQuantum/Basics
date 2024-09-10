bool CRecordSet::sColumnEx(const int iCol, char *sBuf, const int iBufSz, int *iOutLen)
{
	int iLen = 0;

	if(SQL_SUCCEEDED(SQLGetData(hSTMT, iCol, SQL_C_CHAR, sBuf, iBufSz, (SQLINTEGER *)&iLen)))
	{
		if(iLen > iBufSz)
		{
			iLen = iBufSz;
		}

		if(bReplaceSingleQuotes)
		{
			ReplaceSingleQuotes(sBuf, iLen);
		}

		if(bTrimCharData)
		{
			iLen = RTrim(sBuf, iLen);
		}

		if(iOutLen)
		{
			*iOutLen = iLen;
		}
		
		return true;
	}
	else {
		ThrowErrorIfSet();
		return false;
	}
}