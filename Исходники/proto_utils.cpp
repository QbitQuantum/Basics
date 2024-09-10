MIR_APP_DLL(void) ProtoCreateService(PROTO_INTERFACE *pThis, const char* szService, ProtoServiceFunc serviceProc)
{
	char str[MAXMODULELABELLENGTH * 2];
	strncpy_s(str, pThis->m_szModuleName, _TRUNCATE);
	strncat_s(str, szService, _TRUNCATE);
	::CreateServiceFunctionObj(str, (MIRANDASERVICEOBJ)*(void**)&serviceProc, pThis);
}