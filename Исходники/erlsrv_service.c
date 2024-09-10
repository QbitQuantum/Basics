static BOOL new_acl(SaveAclStruct *save_acl){
    HANDLE tokenh;
    TOKEN_DEFAULT_DACL newdacl;
    DWORD required;
    PACL oldacl;
    PACL newacl;
    int i;
    ACL_SIZE_INFORMATION si;
    size_t newsize;
    PSID extra_sid;
    SID_IDENTIFIER_AUTHORITY nt_auth = SECURITY_NT_AUTHORITY;  
    TOKEN_DEFAULT_DACL dummy;

    save_acl->initialized = FALSE;
    if(!OpenProcessToken(GetCurrentProcess(),
			 TOKEN_READ|TOKEN_WRITE,&tokenh)){
      log_warning("Failed to open access token.");
      return FALSE;
    } 
    save_acl->defdacl = &dummy;
    required = sizeof(TOKEN_DEFAULT_DACL);
    GetTokenInformation(tokenh,
			TokenDefaultDacl,
			&(save_acl->defdacl),
			sizeof(TOKEN_DEFAULT_DACL),
			&required);
    if(required == 0){
      log_warning("Failed to get any ACL info from token.");
      CloseHandle(tokenh);
      return FALSE;
    }
    save_acl->defdacl = LocalAlloc(LPTR,required);
    if(!GetTokenInformation(tokenh,
			    TokenDefaultDacl,
			    save_acl->defdacl,
			    required,
			    &required)){
#ifdef HARDDEBUG
	{
	  char *mes;
	  FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,    
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
			(LPTSTR) &mes,    
			0,    
			NULL );
	  log_info(mes);
	  LocalFree(mes);
	}
#endif 
      log_warning("Failed to get default ACL from token.");
      CloseHandle(tokenh);
      return FALSE;
    }

    oldacl = save_acl->defdacl->DefaultDacl;
    if(!GetAclInformation(oldacl, &si, sizeof(si), 
			  AclSizeInformation)){
      log_warning("Failed to get size information for ACL");
      CloseHandle(tokenh);
      return FALSE;
    }

    if(!AllocateAndInitializeSid(&nt_auth,
				 2,
				 SECURITY_BUILTIN_DOMAIN_RID,
				 DOMAIN_ALIAS_RID_ADMINS,
				 0,
				 0,
				 0,
				 0,
				 0,
				 0,
				 &extra_sid)){
      log_warning("Failed to initialize administrator SID.");
      CloseHandle(tokenh);
      return FALSE;
    }

    newsize = si.AclBytesInUse + sizeof(ACL) +
      sizeof(ACCESS_ALLOWED_ACE) + GetLengthSid(extra_sid);
    
    newacl = LocalAlloc(LPTR,newsize);
    
    if(!InitializeAcl(newacl, newsize, ACL_REVISION)){
      log_warning("Failed to initialize new ACL.");
      LocalFree(newacl);
      FreeSid(extra_sid);
      CloseHandle(tokenh);
      return FALSE;
    }

    for(i=0;i<((int)si.AceCount);++i){
      ACE_HEADER *ace_header;
      if (!GetAce (oldacl, i, &ace_header)){
	log_warning("Failed to get ACE from old ACL.");
	LocalFree(newacl);
	FreeSid(extra_sid);
	CloseHandle(tokenh);
	return FALSE;
      }
      if(!AddAce(newacl,ACL_REVISION,0xffffffff,ace_header,
		 ace_header->AceSize)){
	log_warning("Failed to set ACE in new ACL.");
	LocalFree(newacl);
	FreeSid(extra_sid);
	CloseHandle(tokenh);
	return FALSE;
      }
    }  
    if(!AddAccessAllowedAce(newacl,
			   ACL_REVISION2, 
			   PROCESS_ALL_ACCESS,
			   extra_sid)){
   	log_warning("Failed to add system ACE to new ACL.");
	LocalFree(newacl);
	FreeSid(extra_sid);
	return FALSE;
    }
    
    newdacl.DefaultDacl = newacl;
    if(!SetTokenInformation(tokenh,
			    TokenDefaultDacl,
			    &newdacl,
			    sizeof(newdacl))){
      log_warning("Failed to set token information");
      LocalFree(newacl);
      FreeSid(extra_sid);
      CloseHandle(tokenh);
      return FALSE;
    }
    save_acl->initialized = TRUE;
    save_acl->newacl = newacl;
    save_acl->adminsid = extra_sid;
    CloseHandle(tokenh);

    return TRUE;
}