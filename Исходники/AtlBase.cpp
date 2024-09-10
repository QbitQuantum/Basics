STDMETHODIMP CAtlBase::OnWndMsg(PMSG WndMsg, INT* pnRet, BSTR preViewType)
{
	extern BYTE* g_SceneEditorKeyState;

	PMSG pMsg = (PMSG)WndMsg;

	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		g_SceneEditorKeyState[pMsg->wParam] = !!(GetAsyncKeyState(INT(pMsg->wParam)) & 0x8000);
	}

	if (pMsg->message >= WM_MOUSEFIRST && pMsg->message <= WM_MOUSELAST && pMsg->message != WM_MOUSEMOVE || pMsg->message == WM_COMMAND)
	{	
		g_SceneEditorKeyState[VK_LBUTTON] = !!(GetAsyncKeyState(VK_LBUTTON) & 0x8000);
		g_SceneEditorKeyState[VK_MBUTTON] = !!(GetAsyncKeyState(VK_MBUTTON) & 0x8000);
		g_SceneEditorKeyState[VK_RBUTTON] = !!(GetAsyncKeyState(VK_RBUTTON) & 0x8000);
	}
	
	if (_strcmpi(BSTR_TO_STRING(preViewType), "NPC") == 0 && g_NpcInputProxy)
	{
		g_NpcInputProxy->CheckInputEvent(pMsg);
	}
	else if (_strcmpi(BSTR_TO_STRING(preViewType), "Doodad") == 0 && g_DoodadInputProxy)
	{
		g_DoodadInputProxy->CheckInputEvent(pMsg);
	}	

	return S_OK;
}