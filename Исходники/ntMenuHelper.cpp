//----------------------------------------------------------------------------
// Function RemoveSubMenu
// @func    removes submenu from menu
// @rdesc   nothing
// @parm    CFrameWnd    | *pWnd        | frame window to use
// @parm    UINT         | mainMenuItem | main menu item in which's menu submenu is to be added
// @parm    UINT         | itemIndex    | index of submenu in menu
//----------------------------------------------------------------------------
// @prog 
// Anneke Sicherer-Roetman
// @revs 
// 13-03-2000 - First implementation
//----------------------------------------------------------------------------
// @todo 
//----------------------------------------------------------------------------
void RemoveSubMenu(CFrameWnd *pWnd, UINT mainMenuItem, UINT itemIndex)
{
	ASSERT_VALID(pWnd);

	CMenu *pMenuBar = pWnd->GetMenu();
	ASSERT_VALID(pMenuBar);

	CMenu *pSubMenu = pMenuBar->GetSubMenu(mainMenuItem);
	ASSERT_VALID(pSubMenu);

	CMenu *pMenu = pSubMenu->GetSubMenu(itemIndex);
	ASSERT_VALID(pMenu);

	VERIFY(pSubMenu->RemoveMenu(itemIndex, MF_BYPOSITION));
	delete pMenu;
}