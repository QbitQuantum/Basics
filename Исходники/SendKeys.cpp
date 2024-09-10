bool HS_SendKeys::SetToggleState(UINT vk, bool bState)
{
	bool	bInitial;

	if (GetKeyState(vk) & 0x01)
		bInitial = true;						// Was on
	else
		bInitial = false;						// Was off

#ifdef _DEBUG
	Util_DebugMsg("==> HS_SendKeys::SetToggleState : vk=%d, bState=%d, bInitial=%d)\n", vk, bState, bInitial);
#endif

	// Do we need to do anything?
	if (bState == bInitial)
		return bInitial;						// Nope

//	MessageBox(NULL, "Doing Capslock", "", MB_OK);

	keybd_event((BYTE)vk, MapVirtualKey(vk, 0), 0, 0);
	DoKeyDownDelay();
	keybd_event((BYTE)vk, MapVirtualKey(vk, 0), KEYEVENTF_KEYUP, 0);
	DoKeyDelay();

	return bInitial;

} // SetToggleState()