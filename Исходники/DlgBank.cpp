void MakeStringToNum(CString str,LONGLONG &Num)
{
	CString strNumber = str;
	strNumber.Remove(',');
	strNumber.Trim();
	_snscanf(strNumber.GetBuffer(),strNumber.GetLength(),_TEXT("%I64d"),&Num);

	return;
}