BOOL HookIDirect3DDevice9::ShowCursor(LPVOID _this, BOOL bShow)
{
	LOG_API();
	return pD3Dev->ShowCursor(bShow);
}