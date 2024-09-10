bool DeleteRightUsers(UserManager *panel,bool selection)
{
  bool res=false;
  CFarPanelSelection sp((HANDLE)panel,selection);
  if(sp.Number())
  {
    TCHAR warning[TINY_BUFFER];
    if(sp.Number()==1)
    {
      TCHAR Truncated[MAX_PATH];
      _tcscpy(Truncated,sp[0].FileName);
      FSF.TruncPathStr(Truncated,50);
      FSF.sprintf(warning,GetMsg(mDelOne),Truncated);
    }
    else
      FSF.sprintf(warning,GetMsg(mDelUserN+NumberType(sp.Number())),sp.Number());
    const TCHAR *MsgItems[]={GetMsg(mButtonDelete),warning,GetMsg(mButtonDelete),GetMsg(mButtonCancel)};
    if(!Info.Message(&MainGuid,&DelUserMessageGuid,0,NULL,MsgItems,sizeof(MsgItems)/sizeof(MsgItems[0]),2))
    {
      res=true;
      LSA_HANDLE PolicyHandle;
      PolicyHandle=GetPolicyHandle(panel->computer);
      if(PolicyHandle)
      {
        for(int i=0;i<sp.Number();i++)
        {
          if(sp[i].UserData.FreeData)
          {
            LSA_UNICODE_STRING RightName;
            RightName.Buffer=panel->nonfixed;
            RightName.Length=wcslen(RightName.Buffer)*sizeof(wchar_t);
            RightName.MaximumLength=RightName.Length+sizeof(wchar_t);
            LsaRemoveAccountRights(PolicyHandle,GetSidFromUserData(sp[i].UserData.Data),FALSE,&RightName,1);
          }
        }
        LsaClose(PolicyHandle);
      }
    }
  }
  return res;
}