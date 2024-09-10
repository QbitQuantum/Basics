//转换数字
void MakeStringToNum(CString str,SCORE &Num)
{
	CString strNumber = str;
	strNumber.Remove(',');
	strNumber.Trim();

#ifndef _UNICODE
	_snscanf(strNumber.GetBuffer(),strNumber.GetLength(),_TEXT("%I64d"),&Num);
#else
	_snwscanf(strNumber.GetBuffer(),strNumber.GetLength(),_TEXT("%I64d"),&Num);
#endif
	strNumber.ReleaseBuffer();
}