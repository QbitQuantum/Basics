CBasicEventListener::EAction CBasicEventListener::OnChar(HWND hWnd, WPARAM wParam)
{
	if (gEnv && gEnv->pInput)
	{
		// TODO: This code doesn't belong here, should be integrated into CKeyboard to make OnInputEvent and OnInputEventUI consistent across all devices and when in the editor
		SInputEvent event;
		event.modifiers = gEnv->pInput->GetModifiers();
		event.deviceId = eDI_Keyboard;
		event.state = eIS_UI;
		event.value = 1.0f;
		event.pSymbol = 0;//m_rawKeyboard->GetSymbol((lParam>>16)&0xff);
		if (event.pSymbol)
			event.keyId = event.pSymbol->keyId;


		wchar_t tmp[2] = { 0 };
		MultiByteToWideChar(CP_ACP, 0, (char*)&wParam, 1, tmp, 2);

		char szKeyName[4] = {0};
		if (wctomb(szKeyName, (WCHAR)wParam) != -1)
		{
			if (szKeyName[1]==0 && ((unsigned char)szKeyName[0])>=32)
			{
				event.inputChar = tmp[0];
				event.keyName = szKeyName;
				gEnv->pInput->PostInputEvent(event);
			}
		}
	}
	return eA_Default;
}