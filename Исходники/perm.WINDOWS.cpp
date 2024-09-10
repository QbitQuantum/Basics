//
// Determines if user is a member of the global group group_name on domain group_domain
//
//  1 = yes, 0 = no, -1 = error
//
int perm::userInGlobalGroup( const char *account, const char *domain, const char* group_name, const char* group_domain ) {
	
	dprintf(D_FULLDEBUG,"in perm::processGlobalGroupTrustee() looking at group '%s\\%s'\n", 
		(group_domain) ? group_domain : "NULL", (group_name) ? group_name : "NULL" );

	unsigned char* BufPtr; // buffer pointer
	wchar_t group_domain_unicode[MAX_DOMAIN_LENGTH+1];	// computer names restricted to 254 chars
	wchar_t group_name_unicode[MAX_GROUP_LENGTH+1];	// groups limited to 256 chars
	_snwprintf(group_domain_unicode, MAX_DOMAIN_LENGTH+1, L"%S", group_domain);
	_snwprintf(group_name_unicode, MAX_GROUP_LENGTH+1, L"%S", group_name);
	
	GROUP_USERS_INFO_0 *group_members;
	unsigned long entries_read, total_entries;
	NET_API_STATUS status;
	
	// get domain controller name for the domain in question
	status = NetGetDCName( NULL,	// servername
		group_domain_unicode,		// domain to lookup
		&BufPtr						// pointer to buffer containing the name (Unicode string) of the Domain Controller
		);
	
	if (status == NERR_DCNotFound ) {
		dprintf(D_ALWAYS, "perm::NetGetDCName() failed: DCNotFound (domain looked up: %s)\n", group_domain);
		NetApiBufferFree( BufPtr );
		return -1;
	} else if ( status == ERROR_INVALID_NAME ) {
		dprintf(D_ALWAYS, "perm::NetGetDCName() failed: Error Invalid Name (domain looked up: %s)", group_domain);
		NetApiBufferFree( BufPtr );
		return -1;
	}
	
	wchar_t* DomainController = (wchar_t*) BufPtr;
	
	do {
		
		status = NetGroupGetUsers( DomainController,	// domain controller name
			group_name_unicode,							// domain to query
			0,											// level of info
			&BufPtr,									// pointer to buffer containing group members
			16384,										// preferred size of buffer
			&entries_read,								// # entries read
			&total_entries,								// total # of entries
			NULL										// resume pointer
			);
		
		group_members = (GROUP_USERS_INFO_0*) BufPtr;
		
		switch ( status ) {
		case NERR_Success:
		case ERROR_MORE_DATA:
			break;
		case ERROR_ACCESS_DENIED:
		case NERR_InvalidComputer:
		case NERR_GroupNotFound:
			char* DCname = new char[ wcslen( DomainController )+1 ];
			wsprintf(DCname, "%ws", DomainController);
			dprintf(D_ALWAYS, "perm::NetGroupGetUsers failed: (domain: %s, domain controller: %s, total entries: %d, entries read: %d, err=%d)",
				group_domain, DCname, total_entries, entries_read, GetLastError());
			delete[] DCname;
			NetApiBufferFree( BufPtr );
			NetApiBufferFree( DomainController );
			return -1;
		}
		
		DWORD i;
				
		for ( i = 0; i < entries_read; i++ )			{
			
			char t_name[MAX_ACCOUNT_LENGTH+1]; // account names are restricted to 20 chars, but I'm 
								// gonna be safe and say 256.
							 
			snprintf(t_name, MAX_ACCOUNT_LENGTH+1, "%S", group_members[i].grui0_name);
			dprintf(D_FULLDEBUG, "GlobalGroupMember: %s\n", t_name);
			//getDomainAndName( t_str, t_domain, t_name);	
			
			if ( domainAndNameMatch( account, t_name, domain, group_domain ) )
			{
				//delete[] t_str;
				NetApiBufferFree( BufPtr );
				NetApiBufferFree( DomainController );
				return 1;
			}
		
		}
	}while ( status == ERROR_MORE_DATA ); // loop if there's more group members to look at
	
	// exiting the for loop means we didn't find anything
	NetApiBufferFree( BufPtr );
	NetApiBufferFree( DomainController );
	return 0;			
}