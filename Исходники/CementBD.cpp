CMenu* CCementBD::SetModulesExtern()
{
	if(gListModuleExternal.GetCount() == 0) return 0;
    //---------------------------------------------------
    //Формируем меню внешних модулей
    CCementDoc* pDoc = (CCementDoc*)GetDocument();
	HINSTANCE hInst = AfxGetResourceHandle();
    pDoc->m_DefaultMenu = 
        ::LoadMenu(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_KRSCEMENTTYPE));
    if (pDoc->m_DefaultMenu == NULL)
        return 0;

    CMenu* menu = CMenu::FromHandle(pDoc->GetDefaultMenu());
    if(menu)
    {
        int iPos;
        CMenu* pPopup = NULL;
        for(iPos = 0; iPos < (int)menu->GetMenuItemCount(); iPos++)
        {
            if(menu->GetSubMenu(iPos)->GetMenuItemID(0) == ID_NASTROIKA_MODULES) 
            {
                pPopup = menu->GetSubMenu(iPos);
 		int ii = (int)pPopup->GetMenuItemCount();
               break;
            }
        }
        if(pPopup == NULL) return 0;


		CMenu *submenu = menu->GetSubMenu(iPos);
		if(submenu == NULL) return 0;
		int ii = (int)submenu->GetMenuItemCount();


        int cx = ::GetSystemMetrics(SM_CXMENUCHECK);
        int cy = ::GetSystemMetrics(SM_CYMENUCHECK);
        if(pPopup != NULL && gListModuleExternal.GetCount() > 0) 
        {
            pPopup->AppendMenu(MF_SEPARATOR, 0, LPCTSTR(0));

            for(int i = 0; i < gListModuleExternal.GetCount(); i++)
            {
                HICON hIconLarge, hIcon;
//                ExtractIconEx(gListModuleExternal.GetName2(i), 0, &hIconLarge, &hIcon, 1);
				CString Name2 = gListModuleExternal.GetName2txe(i);
				if(Name2.GetLength() == 0) continue;
				ExtractIconEx(Name2, 0, &hIconLarge, &hIcon, 1);
                //HICON hIcon = ExtractIcon(pApp->m_hInstance, gListModuleExternal.GetName2(i), 0);
                if(hIcon != NULL)
                {
                    ICONINFO iconinfo;
                    GetIconInfo(hIcon, &iconinfo);
                    HANDLE hLoad = CopyImage(HANDLE(iconinfo.hbmColor), IMAGE_BITMAP, cx+1, cy+1, LR_COPYFROMRESOURCE);
                    CBitmap *pBmp = CBitmap::FromHandle(HBITMAP(hLoad));
                    CString str;
                    str.Format(" %d", i);
                    str += ".  " + gListModuleExternal.GetName(i);
                    BOOL flg = pPopup->AppendMenu(MF_STRING | MF_ENABLED, ID_MENU_MODULE_EXTERNAL + i, str);
                    pPopup->SetMenuItemBitmaps(i+2, MF_BYPOSITION, pBmp, pBmp);
                    //BOOL res = menu->SetMenuItemBitmaps(2, MF_BYPOSITION, pBmp, pBmp);
                    //int zzz = 0;
                }
            }
        }
        CMDIFrameWnd* frame = ((CMDIChildWnd *) GetParent())->GetMDIFrame();
        frame->MDISetMenu(menu, NULL);
        frame->DrawMenuBar();
    }
    //-------------------------------------------------------------------------
	return menu;
}