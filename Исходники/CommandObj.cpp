bool CCommandObj::FormatCommandInfo(LPCTSTR lpFileName,mdk::NetHost & nClientHost)
{
	OutA(Dbg,("[CCommandServicesObj]Format Command Info[%s] Start."),lpFileName);
	bool bRet = FALSE;
	CHAR szFileName[MAX_PATH] = {0};
	RESOURCEREQUIT rResourceRequit;
//	memcpy_s(rResourceRequit.btResourceBag,MAX_BAG_LEN,m_btCommandBag,MAX_BAG_LEN);


#ifdef UNICODE
	WcsToMbs(lpFileName,szFileName);
#else
	_tcscpy_s(szFileName,MAX_PATH,lpFileName);
#endif

	PathRemoveExtensionA(szFileName);
	strcpy_s(rResourceRequit.szResourceID,szFileName);

	OutA(Dbg,("[CCommandServicesObj]Send Resource Requit Info:[%s] Len:[%d] Start."),rResourceRequit.szResourceID,sizeof(RESOURCEREQUIT));
	bRet = nClientHost.Send((PUCHAR)&rResourceRequit,sizeof(RESOURCEREQUIT));

	Out(Dbg,_T("[CCommandServicesObj]Format Command Info Stop[%d]."),bRet);
	return bRet;
}