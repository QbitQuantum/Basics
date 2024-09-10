/*
 * create_imagelist - イメージリストの作成
 */
static HIMAGELIST create_imagelist(const HINSTANCE hInstance)
{
	HIMAGELIST icon_list;

	icon_list = ImageList_Create(SICONSIZE, SICONSIZE, ILC_COLOR16 | ILC_MASK, 0, 0);
	ImageList_SetBkColor(icon_list, GetSysColor(COLOR_WINDOW));

	imagelist_icon_add(hInstance, icon_list, IDI_ICON_REGIST);
	// フォルダ
	imagelist_fileicon_add(icon_list, work_path, 0);
	imagelist_fileicon_add(icon_list, work_path, SHGFI_OPENICON);
	return icon_list;
}