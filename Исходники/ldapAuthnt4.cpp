LDAPAUTHNT4_API
BOOL CUGP(char * userin,char *password,char *machine,char *groupin,int locdom)
{

	{
	//Handle the command line arguments.
	LPOLESTR pszBuffer = new OLECHAR[MAX_PATH*2];
	LPOLESTR pszBuffer2 = new OLECHAR[MAX_PATH*2];
	LPOLESTR pszBuffer3 = new OLECHAR[MAX_PATH*2];
	LPOLESTR pszBuffer4 = new OLECHAR[MAX_PATH*2];
	mbstowcs( (wchar_t *) pszBuffer, userin, MAX_PATH );
	mbstowcs( (wchar_t *) pszBuffer2, password, MAX_PATH );
	mbstowcs( (wchar_t *) pszBuffer3, machine, MAX_PATH );
	mbstowcs( (wchar_t *) pszBuffer4, groupin, MAX_PATH );
	HRESULT hr = S_OK;
	//Get rootDSE and the domain container's DN.
	IADs *pObject = NULL;
	IADs *pObjectUser = NULL;
	IADs *pObjectGroup = NULL;
	IDirectorySearch *pDS = NULL;
	LPOLESTR szPath = new OLECHAR[MAX_PATH];
	LPOLESTR myPath = new OLECHAR[MAX_PATH];
	VARIANT var;
	////////////FIND SERVER NEEDED FOR NT4
	DWORD dwRet;
	PDOMAIN_CONTROLLER_INFO pdci;
	dwRet = DsGetDcName(NULL, NULL, NULL, NULL	, DS_PDC_REQUIRED, &pdci);
	if (ERROR_SUCCESS!=dwRet) 
		{
			wprintf(L"PDC not found try a rediscover \n");
			dwRet = DsGetDcName(NULL, NULL, NULL, NULL	, DS_DIRECTORY_SERVICE_REQUIRED|DS_FORCE_REDISCOVERY, &pdci);
			if (ERROR_SUCCESS!=dwRet)
			{
				wprintf(L"PDC not found \n");
				delete [] pszBuffer;
				delete [] pszBuffer2;
				delete [] pszBuffer3;
				delete [] pszBuffer4;
				delete [] szPath;
				delete [] myPath;
				return false;
			}
		}
	//////////////////////////////////////////
	wcscpy(szPath,L"LDAP://");
	wcscat(szPath,pdci->DomainControllerName+2);
	wcscat(szPath,L"/rootDSE");
	wprintf(szPath);
	wprintf(L"\n");

	hr = ADsOpenObject(szPath,
					pszBuffer,
					pszBuffer2,
					ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
					IID_IADs,
					(void**)&pObject);
	if (FAILED(hr))
		{
			bool result=false;
			delete [] pszBuffer;
			delete [] pszBuffer2;
			delete [] pszBuffer3;
			delete [] pszBuffer4;
			delete [] szPath;
			delete [] myPath;
			return result;
		}
	hr = pObject->Get(L"defaultNamingContext",&var);

	if (SUCCEEDED(hr))
		{
			wcscpy(szPath,L"LDAP://");
			wcscat(szPath,pdci->DomainControllerName+2);
			wcscat(szPath,L"/");
			wcscat(szPath,var.bstrVal);
			VariantClear(&var);
			if (pObject)
				{
					pObject->Release();
					pObject = NULL;
				}
			wprintf( szPath);
			wprintf(L"\n");
			//Bind to the root of the current domain.
			hr = ADsOpenObject(szPath,pszBuffer,pszBuffer2,
					 ADS_SECURE_AUTHENTICATION,IID_IDirectorySearch,(void**)&pDS);
			if (SUCCEEDED(hr))
				{
					if (SUCCEEDED(hr))
						{
							hr =  FindUserByName(pDS, pszBuffer, &pObjectUser );
							if (FAILED(hr))
								{
									delete [] pszBuffer;
									delete [] pszBuffer2;
									delete [] pszBuffer3;
									delete [] pszBuffer4;
									delete [] szPath;
									delete [] myPath;
									if (pDS) pDS->Release();
									if (pObjectUser) pObjectUser->Release();
									return false;
								}
							if (pObjectUser) pObjectUser->Release();
							///////////////////// VNCACCESS
							hr =  FindGroup(pDS, pszBuffer, &pObjectGroup,pszBuffer4);
							if (pObjectGroup)
										{
											pObjectGroup->Release();
											pObjectGroup = NULL;
										}
							if (SUCCEEDED(hr))
								{
									wprintf(L"FindGroup OK\n");
									IADsGroup *     pIADsG;
									hr = ADsOpenObject( gbsGroup,pszBuffer, pszBuffer2, 
											ADS_SECURE_AUTHENTICATION,IID_IADsGroup, (void**) &pIADsG);
									if (SUCCEEDED(hr))
										{
											VARIANT_BOOL bMember = FALSE;  
											hr = pIADsG->IsMember(gbsMember,&bMember);
											if (SUCCEEDED(hr))
												{
													if (bMember == -1)
														{
															wprintf(L"Object \n\n%s\n\n IS a member of the following Group:\n\n%s\n\n",gbsMember,gbsGroup);
															delete [] pszBuffer;
															delete [] pszBuffer2;
															delete [] pszBuffer3;
															delete [] pszBuffer4;
															delete [] szPath;
															delete [] myPath;
															if (pDS) pDS->Release();
															return true;
														}
													else
														{
															BSTR bsMemberGUID = NULL;
															IDirectoryObject * pDOMember = NULL;
															hr = ADsOpenObject( gbsMember,pszBuffer, pszBuffer2, 
																	ADS_SECURE_AUTHENTICATION,IID_IDirectoryObject, (void**) &pDOMember);
															if (SUCCEEDED(hr))
																{
																	hr = GetObjectGuid(pDOMember,bsMemberGUID);
																	pDOMember->Release();
																	pDOMember  = NULL;
																	if (RecursiveIsMember(pIADsG,bsMemberGUID,gbsMember,true, pszBuffer, pszBuffer2))
																		{
																			delete [] pszBuffer;
																			delete [] pszBuffer2;
																			delete [] pszBuffer3;
																			delete [] pszBuffer4;
																			delete [] szPath;
																			delete [] myPath;
																			if (pDS) pDS->Release();
																			return true;
																		}
																}
													}//else bmember
											}//ismember
									}//iadsgroup 
							}//Findgroup
							
						}//user
				}
		if (pDS) pDS->Release();
		}
	delete [] pszBuffer;
	delete [] pszBuffer2;
	delete [] pszBuffer3;
	delete [] pszBuffer4;
	delete [] szPath;
	delete [] myPath;
	return false;
	}
	return false;
}