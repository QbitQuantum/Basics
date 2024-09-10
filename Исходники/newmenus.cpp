//Returns the number of pages in a menu
//native csdm_menu_pages(menu);
static cell AMX_NATIVE_CALL menu_pages(AMX *amx, cell *params)
{
	GETMENU(params[1]);
	return pMenu->GetPageCount();
}