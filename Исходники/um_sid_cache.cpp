static void add_sid_cache(wchar_t *computer,PSID sid,bool full,wchar_t **username)
{
  *username=(wchar_t*)L"Account Unknown";
  CacheRecord *new_rec=(CacheRecord *)malloc(sizeof(CacheRecord));
  if(new_rec)
  {
    new_rec->sid=(PSID)malloc(GetLengthSid(sid));
    if(new_rec->sid)
    {
      DWORD name_size=0,domain_size=0; SID_NAME_USE type;
      CopySid(GetLengthSid(sid),new_rec->sid,sid);
      if(!LookupAccountSidW(computer,sid,NULL,&name_size,NULL,&domain_size,&type))
        if(GetLastError()==ERROR_INSUFFICIENT_BUFFER)
        {
          new_rec->username=(wchar_t*)malloc((name_size+domain_size)*sizeof(wchar_t));
          if(new_rec->username)
          {
            wchar_t *domain_ptr=new_rec->username,*user_ptr=new_rec->username+domain_size;
            if(domain_size==1)
            {
              user_ptr=new_rec->username;
              domain_ptr=new_rec->username+name_size;
            }
            if(LookupAccountSidW(computer,sid,user_ptr,&name_size,domain_ptr,&domain_size,&type))
            {
              if(domain_size)
                new_rec->username[domain_size]='\\';
              new_rec->username_only=user_ptr;
              new_rec->next=sid_cache;
              sid_cache=new_rec;
              if(full)
              {
                *username=new_rec->username;
              }
              else
              {
                *username=new_rec->username_only;
              }
              return;
            }
          }
        }
    }
    free(new_rec->sid);
    free(new_rec->username);
    free(new_rec);
  }
}