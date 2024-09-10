void CHello2Dlg::OnLbnDblclkList3()
{
	// TODO: 在此添加控件通知处理程序代码
  CMenu   mainmenu;    
  mainmenu.LoadMenu(IDR_SELPROBE);

  CMenu *pM = mainmenu.GetSubMenu(0);
  //remove the existing menu
  CString   str   ;  
  
  for(int   i=pM->GetMenuItemCount()-1;i>=0;i--)   //取得菜单的项数。  
  {    
          pM->GetMenuString(i,str,MF_BYPOSITION);    
          //将指定菜单项的标签拷贝到指定的缓冲区。MF_BYPOSITION的解释见上。    
		  pM->DeleteMenu(i,MF_BYPOSITION);   
  }
  
  CSetting<PROBECFG> prbset;
  prbset.InstallFromFile(PRB_DEFINFO);			
  CString namelist = prbset.GetTitleList('|');	

  int curch = m_chlist.GetCurSel();
  if(curch < 0)
	  return;

  if(m_cfgtype == CFGTYPE_BORE)
  {
	int j = 1;
	pM->AppendMenu(MF_STRING,ID_32771,_T("关闭"));

	while(namelist.Find('|',0) >= 0){
		CString item = namelist.Left(namelist.Find('|',0));
		pM->AppendMenu(MF_STRING,ID_32771+j,item);   //添加新的菜单项		
		namelist.Delete(0,item.GetLength() + 1);
		j = j+1;
	}
	m_cmdbase = ID_32771;
  }
  if(m_cfgtype == CFGTYPE_THMO)
  {
	  //TBEJKNRS
	  m_cmdbase = ID_32771;;
	  pM->AppendMenu(MF_STRING,ID_32771,_T("关闭"));
	  pM->AppendMenu(MF_STRING,ID_32772,_T("T型热电偶"));
	  pM->AppendMenu(MF_STRING,ID_32773,_T("B型热电偶"));
	  pM->AppendMenu(MF_STRING,ID_32774,_T("E型热电偶"));
	  pM->AppendMenu(MF_STRING,ID_32775,_T("J型热电偶"));
	  pM->AppendMenu(MF_STRING,ID_32776,_T("K型热电偶"));
	  pM->AppendMenu(MF_STRING,ID_32777,_T("N型热电偶"));
	  pM->AppendMenu(MF_STRING,ID_32778,_T("R型热电偶"));
	  pM->AppendMenu(MF_STRING,ID_32779,_T("S型热电偶"));
  }
  CRect rect;
  m_chlist.GetClientRect(&rect);
  
  CPoint pt;
  GetCursorPos(&pt);
  SetForegroundWindow();
  pM->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
  return;

}