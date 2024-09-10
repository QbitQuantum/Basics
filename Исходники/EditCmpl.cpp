int ShowMenu(int Offset)
{
  int Msgs[]={MComplete,MComplete,MMenuCfg,MAutoCfg};
  TCHAR Bottom[30];
  FSF.sprintf(Bottom,_T("[%d]"),windows->count());
  FarMenuItem Items[sizeof(Msgs)/sizeof(Msgs[0])];
  TCHAR ItemText[sizeof(Msgs)/sizeof(Msgs[0])][128];
  for(unsigned int i=0;i<(sizeof(Msgs)/sizeof(Msgs[0]));i++)
  {
    Items[i].Flags=0;
    _tcscpy(ItemText[i],GetMsg(Msgs[i]));
    Items[i].Text=ItemText[i];
  }
  ItemText[1][0]=0;
  Items[1].Flags|=MIF_SEPARATOR;
  int MenuCode=0,SelectedItem=0;
  do
  {
    Items[SelectedItem].Flags|=MIF_SELECTED;
    MenuCode=Info.Menu(&MainGuid,&MainMenuGuid,-1,-1,0,FMENU_AUTOHIGHLIGHT|FMENU_WRAPMODE,GetMsg(MEditCmpl),Bottom,_T("Contents"),NULL,NULL,&Items[Offset],sizeof(Msgs)/sizeof(Msgs[0])-Offset);
    Items[SelectedItem].Flags&=~MIF_SELECTED;
    SelectedItem=MenuCode;
    if(MenuCode>=0) MenuCode+=Offset;
    switch(MenuCode)
    {
      case 0: // "OK"
        Complete();
        break;
      case 2: // Menu
        MCmpl->ShowDialog();
        break;
      case 3: // Auto
        ACmpl->ShowDialog();
        break;
    }
  } while(MenuCode>0);
  return TRUE;
}