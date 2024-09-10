bool GetComputer(UserManager *panel,bool selection)
{
  bool res=false;
  if(selection)
  {
    /*
      000000000011111111112222222222333333333344444444
      012345678901234567890123456789012345678901234567
    00                                                00
    01   ÉÍÍÍÍÍÍÍÍÍÍÍ Select Computer ÍÍÍÍÍÍÍÍÍÍÍÍ»   01
    02   º Computer:                              º   02
    03   º ZG                                    ³º   03
    04   º (empty for local system)               º   04
    05   ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼   05
    06                                                06
      000000000011111111112222222222333333333344444444
      012345678901234567890123456789012345678901234567
    */
    static const TCHAR *ComputerHistoryName=_T("UserManager\\Computer");
    FarDialogItem DialogItems[]=
    {
    /*0*/  {DI_DOUBLEBOX,3,1,44,5,{0},NULL,               NULL,0,                    GetMsg(mSelCompTitle),   0,0,{0,0}},
    /*1*/  {DI_TEXT,     5,2, 0,0,{0},NULL,               NULL,0,                    GetMsg(mSelCompLabel),   0,0,{0,0}},
    /*2*/  {DI_EDIT,     5,3,42,0,{0},ComputerHistoryName,NULL,DIF_HISTORY|DIF_FOCUS,_T(""),                  0,0,{0,0}},
    /*3*/  {DI_TEXT,     5,4, 0,0,{0},NULL,               NULL,0,                    GetMsg(mSelCompFootnote),0,0,{0,0}},
    };
    DialogItems[2].Data=panel->computer_ptr;
    CFarDialog dialog;
    int DlgCode=dialog.Execute(MainGuid,GetComputerGuid,-1,-1,48,7,NULL,DialogItems,ArraySize(DialogItems),0,0,ComputerDialogProc,0);
    if(DlgCode!=-1)
    {
      if(dialog.Str(2)[0])
      {
        TCHAR tmp[512];
        if(_tcsncmp(dialog.Str(2),_T("\\\\"),2))
        {
          _tcscpy(tmp,_T("\\\\"));
          _tcscat(tmp,dialog.Str(2));
        }
        else
        {
          _tcscpy(tmp,dialog.Str(2));
        }
        HANDLE hSScr=Info.SaveScreen(0,0,-1,-1);
        const TCHAR *MsgItems[]={_T(""),GetMsg(mOtherConnect)};
        Info.Message(&MainGuid,&MessageGuid,0,NULL,MsgItems,sizeof(MsgItems)/sizeof(MsgItems[0]),0);
        wchar_t temp_computer_name[MAX_PATH];
        _tcscpy(temp_computer_name,tmp);
        DWORD count;
        PVOID buffer;
        if(NetQueryDisplayInformation(temp_computer_name,2,0,1,MAX_PREFERRED_LENGTH,&count,&buffer)==NERR_Success)
        {
          NetApiBufferFree(buffer);
          wcscpy(panel->computer,temp_computer_name);
          panel->computer_ptr=panel->computer;
          res=true;
        }
        else ShowCustomError(mOtherNetNotFound);
        Info.RestoreScreen(hSScr);
      }
      else
      {
        wcscpy(panel->computer,L"");
        panel->computer_ptr=NULL;
        res=true;
      }
    }
  }
  else
  {
    wcscpy(panel->computer,L"");
    panel->computer_ptr=NULL;
    res=true;
  }
  return res;
}