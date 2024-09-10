int CNumEdit::IsValidSymble()const
{
	CString str;
	GetWindowText(str);
	int res = VALID;
	float f;
	char lp[10];
	if ((str.GetLength() == 1) && ((str[0] == '+') || (str[0] == '-'))) 
		res = MINUS_PLUS;
	else
#ifdef UNICODE
    if (swscanf(str, _T("%f%s"), &f, lp) != 1)
        res = INVALID_CHAR;
#else
	if (sscanf(str, _T("%f%s"), &f, lp) != 1) 
		res = INVALID_CHAR;
#endif
	
	return res;
}