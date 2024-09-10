sInt32 CLDAPNode::BindProc ( sLDAPNodeStruct *inLDAPNodeStruct )
{

    sInt32				siResult		= eDSNoErr;
    int					bindMsgId		= 0;
	int					version			= -1;
    sLDAPConfigData	   *pConfig			= nil;
    char			   *ldapAcct		= nil;
    char			   *ldapPasswd		= nil;
    int					openTO			= 0;
	LDAP			   *inLDAPHost		= inLDAPNodeStruct->fHost;
	LDAPMessage		   *result			= nil;
	int					ldapReturnCode	= 0;

	try
	{
		if ( inLDAPNodeStruct == nil ) throw( (sInt32)eDSNullParameter );
		
		if (inLDAPNodeStruct->fLDAPSessionMutex != nil)
		{
			inLDAPNodeStruct->fLDAPSessionMutex->Wait();
		}
        // Here is the bind to the LDAP server
		// Note that there may be stored name/password in the config table
		// ie. always use the config table data if authentication has not explicitly been set
		// use LDAPAuthNodeMap if inLDAPNodeStruct contains a username
		
		//check that we were already here
		if (inLDAPHost == NULL)
		{
			//retrieve the config data
			//don't need to retrieve for the case of "generic unknown" so don't check index 0
			if (( inLDAPNodeStruct->fLDAPConfigTableIndex < gConfigTableLen) && ( inLDAPNodeStruct->fLDAPConfigTableIndex >= 1 ))
			{
				pConfig = (sLDAPConfigData *)gConfigTable->GetItemData( inLDAPNodeStruct->fLDAPConfigTableIndex );
				if (pConfig != nil)
				{
					if ( (pConfig->bSecureUse) && (inLDAPNodeStruct->fUserName == nil) )
					{
						if (pConfig->fServerAccount != nil)
						{
							ldapAcct = new char[1+::strlen(pConfig->fServerAccount)];
							::strcpy( ldapAcct, pConfig->fServerAccount );
						}
						if (pConfig->fServerPassword != nil)
						{
							ldapPasswd = new char[1+::strlen(pConfig->fServerPassword)];
							::strcpy( ldapPasswd, pConfig->fServerPassword );
						}
					}
					else
					{
						if (inLDAPNodeStruct->fUserName != nil)
						{
							ldapAcct = new char[1+::strlen(inLDAPNodeStruct->fUserName)];
							::strcpy( ldapAcct, inLDAPNodeStruct->fUserName );
						}
						if (inLDAPNodeStruct->fAuthCredential != nil)
						{
							if (inLDAPNodeStruct->fAuthType != nil)
							{
								//auth type of clear text means char * password
								if (strcmp(inLDAPNodeStruct->fAuthType,kDSStdAuthClearText) == 0)
								{
									ldapPasswd = new char[1+::strlen((char*)(inLDAPNodeStruct->fAuthCredential))];
									::strcpy( ldapPasswd, (char*)(inLDAPNodeStruct->fAuthCredential) );
								}
							}
							else //default is password
							{
								ldapPasswd = new char[1+::strlen((char*)(inLDAPNodeStruct->fAuthCredential))];
								::strcpy( ldapPasswd, (char*)(inLDAPNodeStruct->fAuthCredential) );
							}
						}
					}
					openTO		= pConfig->fOpenCloseTimeout;
				}
			}

			if (inLDAPNodeStruct->fLDAPConfigTableIndex != 0)
			{
				if (pConfig != nil)
				{
					inLDAPHost = ldap_init( pConfig->fServerName, pConfig->fServerPort );
				}
			}
			else
			{
				inLDAPHost = ldap_init( inLDAPNodeStruct->fServerName, inLDAPNodeStruct->fDirectLDAPPort );
			}
			
			if ( inLDAPHost == nil ) throw( (sInt32)eDSCannotAccessSession );
			
			if (pConfig != nil)
			{
				if ( pConfig->bIsSSL )
				{
					int ldapOptVal = LDAP_OPT_X_TLS_HARD;
					ldap_set_option(inLDAPHost, LDAP_OPT_X_TLS, &ldapOptVal);
				}
			}
			/* LDAPv3 only */
			version = LDAP_VERSION3;
			ldap_set_option( inLDAPHost, LDAP_OPT_PROTOCOL_VERSION, &version );
			
			//heuristic to prevent many consecutive failures with long timeouts
			//ie. forcing quick failures after first failure during a window of
			//the same length as the timeout value
			//NN fLDAPNodeOpenMutex.Wait();
			if ( inLDAPNodeStruct->bHasFailed )
			{
				if ( time( nil ) < inLDAPNodeStruct->fDelayedBindTime )
				{
					//NN fLDAPNodeOpenMutex.Signal();
					throw( (sInt32)eDSCannotAccessSession );
				}
				else
				{
					inLDAPNodeStruct->bHasFailed = false;
					//fDelayedBindTime then is unused so no need to reset
				}
			}
			//NN fLDAPNodeOpenMutex.Signal();

			//this is our and only our LDAP session for now
			//need to use our timeout so we don't hang indefinitely
			bindMsgId = ldap_bind( inLDAPHost, ldapAcct, ldapPasswd, LDAP_AUTH_SIMPLE );
			
			if (openTO == 0)
			{
				ldapReturnCode = ldap_result(inLDAPHost, bindMsgId, 0, NULL, &result);
			}
			else
			{
				struct	timeval	tv;
				tv.tv_sec		= openTO;
				tv.tv_usec		= 0;
				ldapReturnCode	= ldap_result(inLDAPHost, bindMsgId, 0, &tv, &result);
			}

			if ( ldapReturnCode == -1 )
			{
				throw( (sInt32)eDSCannotAccessSession );
			}
			else if ( ldapReturnCode == 0 )
			{
				// timed out, let's forget it
				ldap_abandon(inLDAPHost, bindMsgId);

				//log this timed out connection
				if (pConfig != nil)
				{
					syslog(LOG_INFO,"DSLDAPv3PlugIn: Timed out in attempt to bind to [%s] LDAP server.", pConfig->fServerName);
					syslog(LOG_INFO,"DSLDAPv3PlugIn: Disabled future attempts to bind to [%s] LDAP server for next %d seconds.", pConfig->fServerName, inLDAPNodeStruct->fDelayRebindTry);
				}
				else
				{
					syslog(LOG_INFO,"DSLDAPv3PlugIn: Timed out in attempt to bind to [%s] LDAP server.", inLDAPNodeStruct->fServerName);
					syslog(LOG_INFO,"DSLDAPv3PlugIn: Disabled future attempts to bind to [%s] LDAP server for next %d seconds.", inLDAPNodeStruct->fServerName, inLDAPNodeStruct->fDelayRebindTry);
				}
				//NN fLDAPNodeOpenMutex.Wait();
				inLDAPNodeStruct->bHasFailed = true;
				inLDAPNodeStruct->fDelayedBindTime = time( nil ) + inLDAPNodeStruct->fDelayRebindTry;
				//NN fLDAPNodeOpenMutex.Signal();
				throw( (sInt32)eDSCannotAccessSession );
			}
			else if ( ldap_result2error(inLDAPHost, result, 1) != LDAP_SUCCESS )
			{
				//NN fLDAPNodeOpenMutex.Wait();
				inLDAPNodeStruct->bHasFailed = true;
				inLDAPNodeStruct->fHost = inLDAPHost;
				//NN fLDAPNodeOpenMutex.Signal();
				throw( (sInt32)eDSCannotAccessSession );
			}
			//NN fLDAPNodeOpenMutex.Wait();
			inLDAPNodeStruct->fHost = inLDAPHost;
			//NN fLDAPNodeOpenMutex.Signal();

			//result is consumed above within ldap_result2error
			result = nil;
		}
		
	} // try
	
	catch ( sInt32 err )
	{
		siResult = err;
	}
	
	if (ldapAcct != nil)
	{
		delete (ldapAcct);
		ldapAcct = nil;
	}
	if (ldapPasswd != nil)
	{
		delete (ldapPasswd);
		ldapPasswd = nil;
	}
	
	if (inLDAPNodeStruct->fLDAPSessionMutex != nil)
	{
		inLDAPNodeStruct->fLDAPSessionMutex->Signal();
	}

	return (siResult);
	
}// BindProc