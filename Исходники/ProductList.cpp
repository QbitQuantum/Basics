void ProductList::ShowRMenu()
{
	HMENU hMenu = LoadMenu(IDR_MENU_PRODUCT);
	HMENU hMenuPop = GetSubMenu(hMenu, 0);

	if (GetCount() == 0)
	{
		RemoveMenu(hMenuPop, 1, MF_BYPOSITION);	//删除分隔线
		RemoveMenu(hMenuPop, 1, MF_BYPOSITION);	//删除导出列表
	}
	else if(GetCount() == 1)
		if(GetText(0) == TEXT("<null>"))
			return ;

	SendMessage(getParent(), NM_SETPOPMENULANG, (WPARAM)hMenuPop, (LPARAM)"Product");

	POINT pt;
	::GetCursorPos(&pt);

	::TrackPopupMenuEx(hMenuPop, TPM_BOTTOMALIGN, pt.x, pt.y, getParent(), 0);

	::DestroyMenu(hMenuPop);
}