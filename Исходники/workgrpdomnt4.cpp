WORKGRPDOMNT4_API
BOOL CUGP(char * userin,char *password,char *machine, char *groupin, int locdom)
{             
//	FILE *file;
	bool isNT = true;
	bool isXP =false;
	bool access_vnc=FALSE;
	bool laccess_vnc=FALSE;
	bool localdatabase=false;
	ad_access=false;
	OSVERSIONINFO ovi = { sizeof ovi };
	// determine OS and load appropriate library

	GetVersionEx( &ovi );
	if ( ovi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
		isNT = false;
	if (ovi.dwPlatformId == VER_PLATFORM_WIN32_NT &&
      ovi.dwMajorVersion == 5 &&
      ovi.dwMinorVersion >= 1) isXP=true;

	HINSTANCE hNet = 0, hLoc = 0;

	if ( isNT )
		{
		hNet = LoadLibrary( "netapi32.dll" );
		}
	else
		{
		hLoc = LoadLibrary( "rlocal32.dll" );
		hNet = LoadLibrary( "radmin32.dll" );
		}

	if ( hNet == 0 )
	{
		printf( "LoadLibrary( %s ) failed, gle = %lu\n",
			isNT? "netapi32.dll": "radmin32.dll", GetLastError() );
		return false;
	}

	// locate needed functions
	NetApiBufferFree_t NetApiBufferFree = 0;
	NetGetDCNameNT_t NetGetDCNameNT = 0;
	NetGetDCName95_t NetGetDCName95 = 0;
	NetUserGetGroupsNT_t NetUserGetGroupsNT = 0;
	NetUserGetGroupsNT_t2 NetUserGetGroupsNT2 = 0;
	NetUserGetGroups95_t NetUserGetGroups95 = 0;
	NetWkstaGetInfoNT_t NetWkstaGetInfoNT = 0;
	NetWkstaGetInfo95_t NetWkstaGetInfo95 = 0;

	NetApiBufferFree = (NetApiBufferFree_t) GetProcAddress( hNet, "NetApiBufferFree" );
	if ( NetApiBufferFree == 0 )
	{
		printf( "Oops! GetProcAddress() failed\n" );
		return false;
	}
	
	if ( isNT )
	{
		NetGetDCNameNT = (NetGetDCNameNT_t) GetProcAddress( hNet, "NetGetDCName" );
		NetUserGetGroupsNT = (NetUserGetGroupsNT_t) GetProcAddress( hNet, "NetUserGetLocalGroups" );
		NetUserGetGroupsNT2 = (NetUserGetGroupsNT_t2) GetProcAddress( hNet, "NetUserGetGroups" );
		NetWkstaGetInfoNT = (NetWkstaGetInfoNT_t)GetProcAddress( hNet,"NetWkstaGetInfo" );
		if ( NetGetDCNameNT == 0 || NetUserGetGroupsNT == 0 || NetWkstaGetInfoNT==0 ||NetUserGetGroupsNT2 == 0)
		{
			printf( "Oops! Some functions not found ...\n" );
			return false;
		}
	}
	else
	{
		NetGetDCName95 = (NetGetDCName95_t) GetProcAddress( hLoc, "LocalNetGetDCName" );
		NetUserGetGroups95 = (NetUserGetGroups95_t) GetProcAddress( hNet, "NetUserGetGroupsA" );
		NetWkstaGetInfo95 = (NetWkstaGetInfo95_t)GetProcAddress( hNet,"NetWkstaGetInfoA" );

		if ( NetGetDCName95 == 0 || NetUserGetGroups95 == 0 ||NetWkstaGetInfo95 == 0)
		{
			printf( "Oops! Some functions not found ...\n" );
			return false;
		}
	}
	// find PDC if necessary; else set up server name for call


	byte *buf = 0;
	DWORD rc,rc2,read, total,i,rcdomain;
	char server[MAXLEN * sizeof(wchar_t)];
	char user[MAXLEN * sizeof(wchar_t)];
	char group[MAXLEN * sizeof(wchar_t)];
	char groupname[MAXLEN];
	char domain[MAXLEN * sizeof(wchar_t)];

	
	if ( isNT )	mbstowcs( (wchar_t *) user, userin, MAXLEN );
	else strcpy( user, userin );

	if ( isNT )	mbstowcs( (wchar_t *) group, groupin, MAXLEN );
	else strcpy( group, groupin );
	////////////////////////////////////////////////////////////////////////////////////////////
	////NT
	////////////////////////////////////////////////////////////////////////////////////////////
if ( isNT )
		{

			printf("Client NT4 or later \n");
			///////////////// search DC ///////////////////////////////////
			rcdomain = NetGetDCNameNT( 0, 0, &buf );
			if (rcdomain==2453) printf( "No domain controler found\n");
			if (!rcdomain)
			{
			printf("Domain controler found");
			wcscpy( (wchar_t *) server, (wchar_t *) buf );
			wprintf((wchar_t *)server);
			printf("\n------------------------------\n");
			}
			printf("Checking Local groups for ");
			printf("user: %S\n", _wcsupr((wchar_t *)user));
			printf("group: %S\n", _wcsupr((wchar_t *)group));

			//////////////////////////////////////////////////////////////////
			///////////////// Local groups ///////////////////////////////////
			//////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////
			if (locdom==1 || locdom==3){
				LOCALGROUP_MEMBERS_INFO_2 *bufLMI, *cur;
				DWORD read, total, resumeh, rc, i;
				wchar_t	tempbuf[MAXLEN];
				wchar_t seperator[MAXLEN];      
				
				netlocalgroupgetmembers_t netlocalgroupgetmembers;
				HINSTANCE h = LoadLibrary ("netapi32.dll");
				netlocalgroupgetmembers = (netlocalgroupgetmembers_t) GetProcAddress (h, "NetLocalGroupGetMembers");

				////////////////////// GROUPS///////////////////////////////////////
				mbstowcs( seperator,  "\\", 5 );
				///////////////////////GROUP1/////////////////////////////////////
				resumeh = 0;
				do
				{
					bufLMI = NULL;
					rc = netlocalgroupgetmembers( NULL, (wchar_t *)group, 2, (BYTE **) &bufLMI,BUFSIZE, &read, &total, &resumeh );
					if ( rc == ERROR_MORE_DATA || rc == ERROR_SUCCESS )
						{
							
							for ( i = 0, cur = bufLMI; i < read; ++ i, ++ cur )
								{
									// Note: the capital S in the format string will expect Unicode
									// strings, as this is a program written/compiled for ANSI.
									_wcsupr(cur->lgrmi2_domainandname);
									wcscpy(tempbuf,cur->lgrmi2_domainandname);
									wchar_t *t=wcsstr(tempbuf,seperator);
									t++;
									printf( "%S\n", t );
									if (wcscmp(_wcsupr(t), _wcsupr((wchar_t *)user))==0) 
										{
											laccess_vnc=TRUE;
											printf( "Local: User found in group \n" );
										}
								}
					if ( bufLMI != NULL )
					NetApiBufferFree( bufLMI );
						}
				} while ( rc == ERROR_MORE_DATA );
				
				///////////////////////////////////////////////////////////////////////
			if ( h != 0 )FreeLibrary( h);
			}


			if ( !rcdomain){
				DWORD rc;
				printf( "New added ----  just for testing \n");
				wcscpy( (wchar_t *) server, (wchar_t *) buf );
				byte *buf2 = 0;
				rc2 = NetWkstaGetInfoNT( 0 , 100 , &buf2 ) ;
				if( rc2 ) printf( "NetWkstaGetInfoA() returned %lu \n", rc2);
				else wcstombs( domain, ((WKSTA_INFO_100_NT *) buf2)->wki100_langroup, MAXLEN );
				NetApiBufferFree( buf2 );
				domain[MAXLEN - 1] = '\0';
				printf("Detected domain = %s\n",domain);
				buf2 = 0;
				char userdomain[MAXLEN * sizeof(wchar_t)];
				char userdom[MAXLEN];
				strcpy(userdom,domain);
				strcat(userdom,"\\");
				strcat(userdom,userin);
				mbstowcs( (wchar_t *) userdomain, userdom, MAXLEN );
				printf( "%S\n", userdomain);
				rc = NetUserGetGroupsNT( NULL ,(wchar_t *) userdomain, 0, 1,&buf2, MAX_PREFERRED_LENGTH, &read, &total);
				if ( rc == NERR_Success)
					{
						for ( i = 0; i < read; ++ i )
							{
								wcstombs( groupname, ((LPLOCALGROUP_USERS_INFO_0_NT *) buf2)[i].grui0_name, MAXLEN );	
								groupname[MAXLEN - 1] = '\0'; // because strncpy won't do this if overflow
#ifdef _MSC_VER
								_strupr(groupname);
								_strupr(groupin);
#else
								_strupr(groupname);
								_strupr(groupin);
#endif
								printf( "compare %s %s\n", groupname, group);
								if (strcmp(groupname, groupin)==0) 
								{
									printf( "match ...\n" );
									laccess_vnc=TRUE;
								}
								else printf( "no match ...\n" );
							}
						if (laccess_vnc==TRUE) printf( "group found ...\n" );
						else printf( "No group found \n" );

					}
				NetApiBufferFree( buf2 );
				
			}
	

			 if (locdom==2 || locdom==3) if ( !rcdomain){
				DWORD rc;
				printf( "New added ----  just for testing \n");
				wcscpy( (wchar_t *) server, (wchar_t *) buf );
				byte *buf2 = 0;
				rc2 = NetWkstaGetInfoNT( 0 , 100 , &buf2 ) ;
				if( rc2 ) printf( "NetWkstaGetInfoA() returned %lu \n", rc2);
				else wcstombs( domain, ((WKSTA_INFO_100_NT *) buf2)->wki100_langroup, MAXLEN );
				NetApiBufferFree( buf2 );
				domain[MAXLEN - 1] = '\0';
				printf("Detected domain = %s\n",domain);
				buf2 = 0;
				char userdomain[MAXLEN * sizeof(wchar_t)];
				char userdom[MAXLEN];
				//strcpy(userdom,domain);
				//strcat(userdom,"\\");
				strcpy(userdom,userin);
				mbstowcs( (wchar_t *) userdomain, userdom, MAXLEN );
				printf( "%S\n", userdomain);
				rc = NetUserGetGroupsNT2( (wchar_t *)server,(wchar_t *) userdomain, 0,&buf2, MAX_PREFERRED_LENGTH, &read, &total);
				if ( rc == NERR_Success)
					{
						for ( i = 0; i < read; ++ i )
							{
								wcstombs( groupname, ((LPLOCALGROUP_USERS_INFO_0_NT *) buf2)[i].grui0_name, MAXLEN );	
								groupname[MAXLEN - 1] = '\0'; // because strncpy won't do this if overflow
#ifdef _MSC_VER
								_strupr(groupname);
								_strupr(groupin);
#else
								_strupr(groupname);
								_strupr(groupin);
#endif
								printf( "compare %s %s\n", groupname, group);
								if (strcmp(groupname, groupin)==0) 
								{
									printf( "match ...\n" );
									laccess_vnc=TRUE;
								}
								else printf( "no match ...\n" );
							}
						if (laccess_vnc==TRUE) printf( "group found ...\n" );
						else printf( "No group found \n" );

					}
				NetApiBufferFree( buf2 );
				
			}
		}
	////////////////////////////////////////////////////////////////////////////////////////////
	////9.X
	////////////////////////////////////////////////////////////////////////////////////////////
	if (locdom==2 || locdom==3) if ( !isNT )
		{
			rc = NetGetDCName95( 0, &buf );
			if ( rc ) printf( "NetGetDCName95() returned %lu\n", rc );
			if (rc==2453) 
			{
				printf( "No domain controler found\n");
				return false;
			}
			if ( !rc )
			{
				strcpy( server, (char *) buf );
				byte *buf2 = 0;
				rc = NetWkstaGetInfo95( 0 , 100 , &buf2 ) ;
				if( rc ) printf( "NetWkstaGetInfoA() returned %lu \n", rc);
				else  strncpy( domain, ((WKSTA_INFO_100_95 *) buf2)->wki100_langroup, MAXLEN );
				NetApiBufferFree( buf2 );
				domain[MAXLEN - 1] = '\0';
				NetApiBufferFree( buf );
				buf = 0;
				buf2 = 0;
				////////////////////////////////////////////
				rc = NetUserGetGroups95( server,user, 0, &buf2, 2024, &read, &total);
				if ( rc == NERR_Success)
					{
						for ( i = 0; i < read; ++ i )
							{ 
								strncpy( groupname, ((LPLOCALGROUP_USERS_INFO_0_95 *) buf2)[i].grui0_name, MAXLEN );
								groupname[MAXLEN - 1] = '\0'; // because strncpy won't do this if overflow
#ifdef _MSC_VER
							_strupr(groupname);
#else
							_strupr(groupname);
#endif
								printf( "%s\n", groupname);
								if (strcmp(groupname, group)==0) laccess_vnc=TRUE;
							}
						if (access_vnc==TRUE) printf( "NT: Domain group found ...\n" );
						else printf( "No Domain group found \n" );
					}
				NetApiBufferFree( buf2 );
				buf2=0;
			}
		}
		
	
	if (buf)NetApiBufferFree( buf );
	if ( hNet != 0 )
		FreeLibrary( hNet );
	if ( hLoc != 0 )
		FreeLibrary( hLoc );
	//check user
	if (isNT)
	{

#if _MSC_VER < 1400
		wcstombs( user, (unsigned short *)user, MAXLEN);	
#else
		wcstombs( user, (const wchar_t *)user, MAXLEN);	
#endif
	}

	BOOL logon_OK=false;
	BOOL passwd_OK=false;
#ifdef _MSC_VER
	_strupr(user);
#else
	_strupr(user);
#endif
	passwd_OK=false;
	if (isXP)
		{
			LOGONUSER LU=NULL;
			HMODULE  shell1 = LoadLibrary("advapi32.dll");
			if(shell1!=NULL) LU = (LOGONUSER)GetProcAddress((HINSTANCE)shell1,"LogonUserA");
			if (LU!=NULL)
			{
			HANDLE token;
			if (locdom==2 || locdom==3 ||locdom==1) 
				if (LU(user,domain,password,LOGON32_LOGON_INTERACTIVE,LOGON32_PROVIDER_DEFAULT,&token))
				{	passwd_OK=true;
					if (passwd_OK==TRUE) printf( "Domain password check OK \n" );
					else printf( "Domain password check Failed \n" );
				}
			if (locdom==1 || locdom==3) 
				if (LU(user,".",password,LOGON32_LOGON_INTERACTIVE,LOGON32_PROVIDER_DEFAULT,&token))
				{
				passwd_OK=true;
				if (passwd_OK==TRUE) printf( "Local password check OK \n" );
				}
			}
			FreeLibrary(shell1);

		}
	else
	{
		if (locdom==2 || locdom==3 || locdom==1)
		if (SSPLogonUser(domain,user, password))
		{	passwd_OK=true;
			if (passwd_OK==TRUE) printf( "Domain password check OK \n" );		
		}
		else printf( "Domain password check Failed \n" );

		if (locdom==1 || locdom==3)
		if (SSPLogonUser(".",user, password))
		{
			passwd_OK=true;
			if (passwd_OK==TRUE) printf( "Local password check OK \n" );
		}
		else printf( "Local password check Failed \n" );
		if (locdom==2 || locdom==3)if (SSPLogonUser(domain,"isdiua", "hegbfsa")) {passwd_OK=false;printf( "Guest account block \n" );}
		if (locdom==1 || locdom==3)if (SSPLogonUser(".","isdiua", "hegbfsa")) {passwd_OK=false;printf( "Guest account block \n" );}
	}
	if (access_vnc==TRUE || laccess_vnc==TRUE || ad_access==TRUE)
	{
		if (passwd_OK) 
		{
		logon_OK=true;
		printf( "Acces to vnc  OK \n" );
		}
	}
	return logon_OK;
	
}