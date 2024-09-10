BOOL WINAPI CRTfunc(LPWSTR *Buf,size_t cnt,BSTR arg1,BSTR arg2,BSTR arg3,BSTR arg4,BSTR arg5)
{
	UINT len = SysStringByteLen( arg1 );
	memcpy(*Buf, arg1, len);

	LPWSTR p = *Buf+ SysStringLen ( arg1 );
	len = SysStringByteLen( arg2 );
	memcpy(p, arg2, len);

	p = p+ SysStringLen ( arg2 );
	len = SysStringByteLen( arg3 );
	memcpy(p, arg3, len);

	p = p+ SysStringLen ( arg3 );
	len = SysStringByteLen( arg4 );
	memcpy(p, arg4, len);

	p = p+ SysStringLen ( arg4 );
	len = SysStringByteLen( arg5 );
	memcpy(p, arg5, len);

	return TRUE;
}