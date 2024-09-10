static NOINLINE void GetFrameName(int Id,tchar_t* Out,int OutLen)
{
	tcscpy_s(Out,OutLen,PlayerComment(Id));
	tcscat_s(Out,OutLen,T("="));
}