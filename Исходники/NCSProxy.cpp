bool CNCSProxy::Find() {
	char chName[MAX_PATH];
	string sProxyName = "";
	string sBypassList = "";
        
        if( sm_bUseGlobalProxy ) {
            sm_mProxy.Lock();
            
            m_nProxyPort = sm_nProxyPort;
            m_sProxyName = sm_sProxyName;
            sBypassList = sm_sBypassList;
            
            sm_mProxy.UnLock();
            
            // create bypass list
            CreateBypassList( sBypassList );
            
            return true;
        }
#ifdef WIN32	
	else if(GetModuleFileNameA(NULL, chName, MAX_PATH) &&	_strlwr(chName) && strstr(chName, "netscape.exe") ) { // netscape
		
		if( !GetNetscapeProxyInfo(sProxyName, sBypassList) )
			return false;		
	} else if(GetModuleFileNameA(NULL, chName, MAX_PATH) &&	_strlwr(chName) &&  // direct
		(strstr(chName, "inetinfo.exe") || strstr(chName, "dllhost.exe")  || strstr(chName, "mtx.exe"))) {
		// Running inside IIS
		// use DIRECT!
		return false;
	} else { // ie
		if( !GetIEProxyInfo( sProxyName, sBypassList ) )
			return false;
	}
#elif defined( POSIX )
        else {
            return false;