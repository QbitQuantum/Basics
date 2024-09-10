void
O2Profile_SAX2Handler::
endElement(const XMLCh* const uri
		 , const XMLCh* const localname
		 , const XMLCh* const qname)
{
	switch (CurElm) {
		case PROF_XMLELM_ID:
			Profile->ID.assign(buf.c_str(), buf.size());
			break;
		case PROF_XMLELM_PRIVKEY:
			Profile->PrivKey.assign(buf.c_str(), buf.size());
			break;
		case PROF_XMLELM_PUBKEY:
			Profile->PubKey.assign(buf.c_str(), buf.size());
			break;
		case PROF_XMLELM_IP:
			Profile->IP = e2ip(buf.c_str(), buf.size());
			break;
		case PROF_XMLELM_P2PPORT:
			Profile->P2PPort = (ushort)wcstoul(buf.c_str(), NULL, 10);
			break;
		case PROF_XMLELM_PROXYPORT:
			Profile->ProxyPort = (ushort)wcstoul(buf.c_str(), NULL, 10);
			break;
		case PROF_XMLELM_ADMINPORT:
			Profile->AdminPort = (ushort)wcstoul(buf.c_str(), NULL, 10);
			break;
		case PROF_XMLELM_NAME:
			if (buf.size() <= O2_MAX_NAME_LEN) {
				Profile->SetNodeName(buf.c_str());
			}
			break;
		case PROF_XMLELM_COMMENT:
			if (buf.size() <= O2_MAX_COMMENT_LEN) {
				for (size_t i = 0; i < buf.size(); i++) {
					if (buf[i] == L'\n')
						Profile->Comment += L"\r\n";
					else
						Profile->Comment += buf[i];
				}
			}
			break;
		case PROF_XMLELM_DBDIR:
			Profile->SetDBDir(buf.c_str());
			break;
		case PROF_XMLELM_CACHEROOT:
			Profile->SetCacheRoot(buf.c_str());
			break;
		case PROF_XMLELM_ADMINROOT:
			Profile->SetAdminRoot(buf.c_str());
			break;
		case PROF_XMLELM_ADMIN_BROWSER_TYPE:
			Profile->AdminBrowserType = buf;
			break;
		case PROF_XMLELM_ADMIN_BROWSER_PATH:
			Profile->AdminBrowserPath = buf;
			break;
		case PROF_XMLELM_UPNP_ADAPTERNAME:
			unicode2ascii(buf, Profile->UPnPAdapterName);
			break;
		case PROF_XMLELM_UPNP_LOCATION:
			unicode2ascii(buf, Profile->UPnPLocation);
			break;
		case PROF_XMLELM_UPNP_SERVICEID:
			unicode2ascii(buf, Profile->UPnPServiceId);
			break;

		case PROF_XMLELM_LIMIT:
			if (plimit)
				*plimit = wcstoul(buf.c_str(), NULL, 10);
			break;
		case PROF_XMLELM_SIZE_T:
			if (puint64)
				*puint64 = _wcstoui64(buf.c_str(), NULL, 10);
			break;
		case PROF_XMLELM_BOOL:
			*pbool = buf[0] == '1' ? true : false;
			break;
	}

	buf = L"";

	CurElm = PROF_XMLELM_NONE;
	if (!MATCHLNAME(L"profile"))
		return;

	if (Profile->PrivKey.size() != RSA_PRIVKEY_SIZE
			|| Profile->PubKey.size() != RSA_PUBKEY_SIZE) {
		Profile->SetRSAKey(NULL, 0, NULL, 0);
	}
}