VOID ACLStr::Append(IN LPCTSTR str)
{
	_Concat(STRLEN(str), str);
}	//	Append