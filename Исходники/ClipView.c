/* ************************************
* void WINAPI SetAutoView(HWND hwnd)
* 获取粘贴板的主要格式，并设置显示方式
**************************************/
void WINAPI SetAutoView(HWND hwnd)
{
	static UINT auPriorityList[] = {
		CF_OWNERDISPLAY,
		CF_TEXT,
		CF_ENHMETAFILE,
		CF_BITMAP
	};
	// 获取粘贴板主要格式
	// 设置显示模式
	// uFormat在WM_PAINT消息时引用
	uFormat = GetPriorityClipboardFormat(auPriorityList, 4);
	fAuto = TRUE;

	InvalidateRect(hwnd, NULL, TRUE);
	UpdateWindow(hwnd);
}