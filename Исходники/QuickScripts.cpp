void CQuickScripts::_PrepareViewMenu(int cItems)
{
    if (m_wndButtonViews.m_menu == NULL)
    {
        CMenu menu;
        if (menu.LoadMenu(IDR_MENUVIEWS))
        {
            // We only need to do this once...
            m_wndButtonViews.m_menu.Attach(menu.Detach());
        }
    }
    if (m_wndButtonViews.m_menu)
    {
        UINT nID;
        if (_GetMenuItem("placeholder", &m_wndButtonViews.m_menu, &nID))
        {
            CMenu *pMenuSub = m_wndButtonViews.m_menu.GetSubMenu(nID);

            // Clear the menu out first.
            UINT cItemsInMenu = pMenuSub->GetMenuItemCount();
            while (cItemsInMenu > 0)
            {
                pMenuSub->RemoveMenu(0, MF_BYPOSITION);
                cItemsInMenu--;
            }

            // And rebuild
            for (int iIndex = 0; iIndex < cItems; iIndex++)
            {
                MENUITEMINFO mii = { 0 };
                mii.cbSize = sizeof(mii);
                mii.fMask = MIIM_ID | MIIM_STRING;
                mii.wID = ID_GOTOVIEW1 + iIndex;
                mii.dwTypeData = "foo";
                pMenuSub->InsertMenuItem(ID_GOTOVIEW1 + iIndex, &mii, FALSE);
                //menu.InsertMenuItem(ID_GOTOVIEW1 + iIndex, &mii, FALSE);
            }
        }
    }
    m_wndButtonViews.EnableWindow(cItems > 0);
}