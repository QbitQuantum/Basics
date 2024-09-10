int CIrcSocket::OnLayerCallback(const CAsyncSocketExLayer* pLayer, int nType, int nParam1, int nParam2)
{
	if (nType == LAYERCALLBACK_LAYERSPECIFIC)
	{
		ASSERT( pLayer );
		if (pLayer == m_pProxyLayer)
		{
			switch (nParam1)
			{
				case PROXYERROR_NOCONN:{
					CString strError(_T("IRC socket: Can't connect to proxy server"));
					CString strErrInf;
					if (nParam2 && GetErrorMessage(nParam2, strErrInf))
						strError += _T(" - ") + strErrInf;
					LogWarning(LOG_STATUSBAR, _T("%s"), strError);
					break;
				}
				case PROXYERROR_REQUESTFAILED:{
					CString strError(_T("IRC socket: Proxy server request failed"));
					if (nParam2){
						strError += _T(" - ");
						strError += (LPCSTR)nParam2;
					}
					LogWarning(LOG_STATUSBAR, _T("%s"), strError);
					break;
				}
				case PROXYERROR_AUTHTYPEUNKNOWN:
					LogWarning(LOG_STATUSBAR, _T("IRC socket: Required authentification type reported by proxy server is unknown or unsupported"));
					break;
				case PROXYERROR_AUTHFAILED:
					LogWarning(LOG_STATUSBAR, _T("IRC socket: Proxy server authentification failed"));
					break;
				case PROXYERROR_AUTHNOLOGON:
					LogWarning(LOG_STATUSBAR, _T("IRC socket: Proxy server requires authentification"));
					break;
				case PROXYERROR_CANTRESOLVEHOST:
					LogWarning(LOG_STATUSBAR, _T("IRC socket: Can't resolve host of proxy server"));
					break;
				default:{
					LogWarning(LOG_STATUSBAR, _T("IRC socket: Proxy server error - %s"), GetProxyError(nParam1));
				}
			}
		}
	}
	return 1;
}