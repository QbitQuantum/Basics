void ServiceStart(BOOL aService)
{
  DWORD ThreadID,i;
  wchar_t filename[MAX_PATH],access_filename[MAX_PATH];
  InitInfo();
  InitNotify();
  {
    HANDLE token; PTOKEN_USER token_user=NULL;
    SID_IDENTIFIER_AUTHORITY SIDAuthSystem={SECURITY_NT_AUTHORITY}; PSID pSystemSid=NULL;
    if(AllocateAndInitializeSid(&SIDAuthSystem,1,SECURITY_LOCAL_SYSTEM_RID,0,0,0,0,0,0,0,&pSystemSid))
    {
      if(OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&token))
      {
        token_user=(PTOKEN_USER)DefaultTokenInformation(token,TokenUser);
        if(token_user)
        {
          if((token_user->User.Sid)&&(pSystemSid)&&(IsValidSid(token_user->User.Sid))&&(IsValidSid(pSystemSid))&&(EqualSid(token_user->User.Sid,pSystemSid)))
            IsSystem=TRUE;
          free(token_user);
        }
        CloseHandle(token);
      }
      FreeSid(pSystemSid);
    }
  }
  //get security from file.
  EnablePrivilege(L"SeSecurityPrivilege");
  if(!pipe_sd&&GetModuleFileNameW(NULL,filename,sizeofa(filename)))
  {
    wchar_t *filename_ptr;
    DWORD res=GetFullPathNameW(filename,sizeofa(access_filename),access_filename,&filename_ptr);
    if(res&&(res<sizeofa(access_filename))&&filename_ptr)
    {
      DWORD needed;
      wcscpy(filename_ptr,ACCESS_NAMEW);
      if(!GetFileSecurityW(access_filename,DACL_SECURITY_INFORMATION|SACL_SECURITY_INFORMATION,NULL,0,&needed))
        if(GetLastError()==ERROR_INSUFFICIENT_BUFFER)
        {
          pipe_sd=(PSECURITY_DESCRIPTOR)malloc(needed);
          if(pipe_sd)
          {
            if(!GetFileSecurityW(access_filename,DACL_SECURITY_INFORMATION|SACL_SECURITY_INFORMATION,pipe_sd,needed,&needed))
            {
              free(pipe_sd);
              pipe_sd=NULL;
            }
          }
        }
    }
  }
  //create default security
  if(!pipe_sd)
  {
    PSID pAccessSid=NULL;
    PSID pSystemSid=NULL;
    SID_IDENTIFIER_AUTHORITY SIDAuthLocal={SECURITY_LOCAL_SID_AUTHORITY};
    SID_IDENTIFIER_AUTHORITY SIDAuthEveryone={SECURITY_WORLD_SID_AUTHORITY};
    SID_IDENTIFIER_AUTHORITY SIDAuthSystem={SECURITY_NT_AUTHORITY};
    DWORD sd_size=SECURITY_DESCRIPTOR_MIN_LENGTH+sizeof(ACL);
    PACL pAcl=NULL;

    if(GetAllowNetwork()?AllocateAndInitializeSid(&SIDAuthEveryone,1,SECURITY_WORLD_RID,0,0,0,0,0,0,0,&pAccessSid):AllocateAndInitializeSid(&SIDAuthLocal,1,SECURITY_LOCAL_RID,0,0,0,0,0,0,0,&pAccessSid))
    {
      if(AllocateAndInitializeSid(&SIDAuthSystem,1,SECURITY_LOCAL_SYSTEM_RID,0,0,0,0,0,0,0,&pSystemSid))
      {
        sd_size+=2*(sizeof(ACCESS_ALLOWED_ACE)-sizeof(DWORD))+GetLengthSid(pAccessSid)+GetLengthSid(pSystemSid);
        pipe_sd=(PSECURITY_DESCRIPTOR)malloc(sd_size);
        if(pipe_sd)
        {
          pAcl=(PACL)(((char *)pipe_sd)+SECURITY_DESCRIPTOR_MIN_LENGTH);
          if(!(InitializeAcl(pAcl,sd_size-SECURITY_DESCRIPTOR_MIN_LENGTH,ACL_REVISION)&&AddAccessAllowedAce(pAcl,ACL_REVISION,FILE_ALL_ACCESS,pAccessSid)&&AddAccessAllowedAce(pAcl,ACL_REVISION,FILE_ALL_ACCESS,pSystemSid)&&InitializeSecurityDescriptor(pipe_sd,SECURITY_DESCRIPTOR_REVISION)&&SetSecurityDescriptorDacl(pipe_sd,TRUE,pAcl,FALSE)))
          {
            free(pipe_sd);
            pipe_sd=NULL;
          }
        }
        FreeSid(pSystemSid);
      }
      FreeSid(pAccessSid);
    }
  }
  for(i=0;i<GetThreadCount();i++)
  {
    threads[i]=CreateThread(NULL,0,ServiceStartThread,(void *)(DWORD_PTR)i,CREATE_SUSPENDED,&ThreadID);
    if(threads[i])
    {
      SetThreadPriority(threads[i],GetHearPriority());
      ResumeThread(threads[i]);
    }
  }
  WaitStartEvent(aService);
  if(aService) ReportStatusToSCMgr(SERVICE_RUNNING,NO_ERROR,0);
}