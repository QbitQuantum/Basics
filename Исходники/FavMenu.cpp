void CFavMenu::LoadIEFav(HMENU &fav_menu)
{
//	錯誤，這樣會把其他favorite和history的CFavMenu <-> HMENU對應刪除
//	favmenus.RemoveAll();
//	改成下列方式，因為上面已經 DestroyMenu( fav_menu )，所以可以很投機取巧的
//	利用 IsMenu 來檢查，移除 favmenu 中已經無效的 Handles
	int i;	//	此 i 在稍後的程式還有使用
	for (i = favmenus.GetSize() - 1;i >= 0;i--)	//搜尋看是否為CFavMenu
		if (!IsMenu(reinterpret_cast<HMENU>(favmenus[i])))
			favmenus.RemoveAt(i);
	//	刪除特定位置第i個 item 後，其後的array都會往前 shift 1，
	//	但是不用管他，因為是由後往前檢查，所以i後面的都已經檢查過

	DestroyMenu(fav_menu);
	web_fav.RemoveAll();

	CString favdir = GetIEFavDir();

	max_height = GetSystemMetrics(SM_CYSCREEN) - 64;
	item_height = GetSystemMetrics(SM_CYMENU);

	UINT id = ID_FIRST_WEB_FAVORITE;
	fav_menu = CreatePopupMenu();
	AddToIEFav(fav_menu, favdir, id);
}