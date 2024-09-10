static LONG_PTR WINAPI NameDlgProc(HANDLE hDlg,int Msg,int Param1,LONG_PTR Param2)
{
  Splited *DlgParams=(Splited *)Info.SendDlgMessage(hDlg,DM_GETDLGDATA,0,0);
  switch(Msg)
  {
    case DN_DRAWDLGITEM:
      if(Param1>0)
      {
        DWORD written; COORD coord;
        SMALL_RECT Rect;
        Info.SendDlgMessage(hDlg,DM_GETDLGRECT,0,(LONG_PTR)&Rect);
        coord.X=Rect.Left+((FarDialogItem *)Param2)->X1;
        coord.Y=Rect.Top+((FarDialogItem *)Param2)->Y1;
        wchar_t *string=DlgParams->Name[Param1-1];
        DWORD string_len=(DWORD)wcslen(string);
        WriteConsoleOutputCharacterW(DlgParams->Console,string,string_len,coord,&written);
      }
      break;
    case DN_ENTERIDLE:
      Info.SendDlgMessage(hDlg,DM_SETREDRAW,0,0);
      break;
  }
  return Info.DefDlgProc(hDlg,Msg,Param1,Param2);
}