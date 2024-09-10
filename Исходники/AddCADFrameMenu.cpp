bool CAddCADFrameMenu::GetAcadMenuGroup(IAcadMenuGroup  **pVal,LPCTSTR menuname)
{
 IAcadApplication *acadApp = NULL;
 HRESULT hr = S_OK;
 
 if(!GetAcadApplication(acadApp))
  return false;
 
 LPDISPATCH  pTempDisp = NULL;
 IAcadMenuGroups *mnuGrps = NULL;
 long cnt = 0, cntmnu=0;
 
 //得到菜单组集
 hr = acadApp->get_MenuGroups(&mnuGrps);
 if (FAILED(hr))
 {
  acadApp->Release();
  return false;
 }
 acadApp->Release();
 
 mnuGrps->get_Count(&cnt);
 
 //得到菜单组
 IAcadMenuGroup *mnuGrp = NULL;
 IAcadPopupMenus  *mnus = NULL;
 IAcadPopupMenu *pPopUpMenu=NULL;
 
 VARIANT  vtName,vtMenu;
 vtName.vt = VT_I4;
 vtMenu.vt = VT_I4;

 BSTR  mnuName;
 bool found = false ;
 for (long i=0; i < cnt; i++)
 {
  vtName.lVal = i;
  hr = mnuGrps->Item(vtName, &mnuGrp);
  if (FAILED(hr))
  {
   return false;
  }
  
  mnuGrp->get_Menus(&mnus);

  mnus->get_Count(&cntmnu);

  for(long j=0;j<cntmnu;j++)
  {
   vtMenu.lVal=j;
   hr=mnus->Item(vtMenu,&pPopUpMenu);
   if(FAILED(hr))
    continue;

   pPopUpMenu->get_Name(&mnuName);
   pPopUpMenu->Release();

   CString sMenuName(mnuName);
   SysFreeString(mnuName);
   
   sMenuName.Replace("&","");//debug
   if(sMenuName.CompareNoCase(menuname)==0)
   {
    found=true;
    *pVal = mnuGrp;
    break;
   }
  }

  mnus->Release();

  if(found)
  {
   break;
  }
  else
  {
   mnuGrp->Release();
  }
 }

 mnuGrps->Release();
 
 return found;
}