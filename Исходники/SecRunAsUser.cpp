eResult CSecRunAsUser::PrepareUser(){
	CoInitialize(NULL);
	bool bResult = false;
	if (!LoadAPI())
		return RES_FAILED;

	try{
		IADsContainerPtr pUsers;
		try{
			IADsWinNTSystemInfoPtr pNTsys;
			if (CoCreateInstance(CLSID_WinNTSystemInfo,NULL,CLSCTX_INPROC_SERVER,IID_IADsWinNTSystemInfo,(void**)&pNTsys) != S_OK)
			    throw CString(_T("Failed to create IADsWinNTSystemInfo"));
			// check if we are already running on our eMule Account
			// todo: check if the current account is an administrator
			
			CComBSTR bstrUserName;
			pNTsys->get_UserName(&bstrUserName);
			m_strCurrentUser = bstrUserName;

			if (m_strCurrentUser == EMULEACCOUNTW){ 
				m_bRunningAsEmule = true;
			    throw CString(_T("Already running as eMule_Secure Account (everything is fine)"));
			}
			CComBSTR bstrCompName;
			pNTsys->get_ComputerName(&bstrCompName);
			CStringW cscompName = bstrCompName;

			CComBSTR bstrDomainName;
			pNTsys->get_DomainName(&bstrDomainName);
			m_strDomain = bstrDomainName;
		
			ADSPath.Format(L"WinNT://%s,computer",cscompName);
			if ( !SUCCEEDED(ADsGetObject(ADSPath.AllocSysString(),IID_IADsContainer,(void **)&pUsers)) )
			    throw CString(_T("Failed ADsGetObject()"));

			IEnumVARIANTPtr pEnum; 
			ADsBuildEnumerator (pUsers,&pEnum);

			IADsUserPtr pChild;
			_variant_t vChild;			  
			while( ADsEnumerateNext (pEnum,1,&vChild,NULL) == S_OK )
			{	
				if (vChild.pdispVal->QueryInterface(IID_IADsUser,(void **)&pChild) != S_OK)
					continue;
				//If the object in the container is user then get properties
				CComBSTR bstrName; 
				pChild->get_Name(&bstrName);
				CStringW csName= bstrName;
				
				// find the emule user account if possible
				if ( csName == EMULEACCOUNTW ){
					// account found, set new random password and save it
					m_strPassword = CreateRandomPW();
					if ( !SUCCEEDED(pChild->SetPassword(m_strPassword.AllocSysString())) )
					    throw CString(_T("Failed to set password"));

					bResult = true;
					break;
				}
			}

		}
		catch(CString error){
			// clean up and abort
			theApp.QueueDebugLogLine(false, _T("Run as unpriveleged user: Exception while preparing user account: %s!"), error);
			CoUninitialize();
			if (m_bRunningAsEmule)
				return RES_OK;
			else
				return RES_FAILED;
		}
		if (bResult || CreateEmuleUser(pUsers) ){
			bResult = SetDirectoryPermissions();
		}
	}
	catch(...){
		// clean up and abort
		theApp.QueueDebugLogLine(false, _T("Run as unpriveleged user: Unexpected fatal error while preparing user account!"));
		CoUninitialize();
		return RES_FAILED;
	}



	CoUninitialize();
	FreeAPI();
	if (bResult)
		return RES_OK_NEED_RESTART;
	else
		return RES_FAILED;
}