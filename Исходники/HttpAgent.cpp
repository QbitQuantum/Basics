template<class T, USHORT default_port> BOOL CHttpAgentT<T, default_port>::StartHttp(TSocketObj* pSocketObj)
{
	if(!pSocketObj->HasConnected())
	{
		::SetLastError(ERROR_INVALID_STATE);
		return FALSE;
	}

	CCriSecLock locallock(pSocketObj->csSend);

	if(!TSocketObj::IsValid(pSocketObj))
	{
		::SetLastError(ERROR_OBJECT_NOT_FOUND);
		return FALSE;
	}

	if(!pSocketObj->HasConnected())
	{
		::SetLastError(ERROR_INVALID_STATE);
		return FALSE;
	}

	THttpObj* pHttpObj = FindHttpObj(pSocketObj);

	if(pHttpObj != nullptr)
	{
		::SetLastError(ERROR_ALREADY_INITIALIZED);
		return FALSE;
	}

	DoStartHttp(pSocketObj);

	if(!IsSecure())
		FireHandShake(pSocketObj);
	else
	{
#ifdef _SSL_SUPPORT
		if(IsSSLAutoHandShake())
			StartSSLHandShake(pSocketObj);
#endif
	}

	return TRUE;
}