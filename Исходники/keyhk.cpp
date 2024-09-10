LRESULT CALLBACK
KeyHookMsg(int code, WPARAM w, LPARAM l)
{
	if(code >= 0 && IsWindow(g_targetWnd))
	{
		PKEYINFO keyInfo = (PKEYINFO) &l;

		if(!keyInfo->extended && !keyInfo->alt && !keyInfo->notPressed)
		{
			BYTE keyState[256];
			WORD ch=0;

			GetKeyboardState(keyState);
			keyState[VK_CONTROL] = 0;
			if(ToAscii((UINT) w, keyInfo->scanCode, keyState, &ch, 0) == 1)
			{

				SendMessageTimeout(	g_targetWnd,
									g_callbackMsg, 
									ch, 
									l, 
									SMTO_BLOCK|SMTO_ABORTIFHUNG, 
									50, 
									NULL	);
			}
		}
	}

    return CallNextHookEx(NULL, code, w, l);
}