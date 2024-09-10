void HKStringEntryLogic::Update()
{
	bool shiftL = !!MFInput_Read(Key_LShift, IDD_Keyboard);
	bool shiftR = !!MFInput_Read(Key_RShift, IDD_Keyboard);
	bool ctrlL = !!MFInput_Read(Key_LControl, IDD_Keyboard);
	bool ctrlR = !!MFInput_Read(Key_RControl, IDD_Keyboard);

	int keyPressed = 0;

	bool shift = shiftL || shiftR;
	bool ctrl = ctrlL || ctrlR;

#if defined(MF_WINDOWS)
	if(ctrl && MFInput_WasPressed(Key_C, IDD_Keyboard) && selectionStart != selectionEnd)
	{
		BOOL opened = OpenClipboard(apphWnd);

		if(opened)
		{
			int selMin = MFMin(selectionStart, selectionEnd);
			int selMax = MFMax(selectionStart, selectionEnd);

			int numChars = selMax-selMin;

			HANDLE hData = GlobalAlloc(GMEM_MOVEABLE, numChars + 1);
			char *pString = (char*)GlobalLock(hData);

			MFString_Copy(pString, GetRenderString().SubStr(selMin, numChars).CStr());

			GlobalUnlock(hData);

			EmptyClipboard();
			SetClipboardData(CF_TEXT, hData);

			CloseClipboard();
		}
	}
	else if(ctrl && MFInput_WasPressed(Key_X, IDD_Keyboard) && selectionStart != selectionEnd)
	{
		BOOL opened = OpenClipboard(apphWnd);

		if(opened)
		{
			int selMin = MFMin(selectionStart, selectionEnd);
			int selMax = MFMax(selectionStart, selectionEnd);

			int numChars = selMax-selMin;

			HANDLE hData = GlobalAlloc(GMEM_MOVEABLE, numChars + 1);
			char *pString = (char*)GlobalLock(hData);

			MFString_Copy(pString, GetRenderString().SubStr(selMin, numChars).CStr());

			GlobalUnlock(hData);

			EmptyClipboard();
			SetClipboardData(CF_TEXT, hData);

			CloseClipboard();

			ClearSelection();
		}
	}
	else if(ctrl && MFInput_WasPressed(Key_V, IDD_Keyboard))
	{
		BOOL opened = OpenClipboard(apphWnd);

		if(opened)
		{
			int selMin = MFMin(selectionStart, selectionEnd);
			int selMax = MFMax(selectionStart, selectionEnd);

			int numChars = selMax-selMin;

			HANDLE hData = GetClipboardData(CF_TEXT);
			MFString paste((const char*)GlobalLock(hData), true);

			buffer.Replace(selMin, numChars, paste);

			GlobalUnlock(hData);

			cursorPos = selMin + paste.NumBytes();
			selectionStart = selectionEnd = cursorPos;

			GlobalUnlock(hData);

			CloseClipboard();

			if((numChars || cursorPos != selMin) && changeCallback)
				changeCallback(buffer.CStr());
		}
	}
	else
#endif
	{
		// check for new keypresses
		for(int a=0; a<255; a++)
		{
			if(MFInput_WasPressed(a, IDD_Keyboard))
			{
				keyPressed = a;
				holdKey = a;
				repeatDelay = gRepeatDelay;
				break;
			}
		}

		// handle repeat keys
		if(holdKey && MFInput_Read(holdKey, IDD_Keyboard))
		{
			repeatDelay -= MFSystem_TimeDelta();
			if(repeatDelay <= 0.f)
			{
				keyPressed = holdKey;
				repeatDelay += gRepeatRate;
			}
		}
		else
			holdKey = 0;

		// if there was a new key press
		if(keyPressed)
		{
			switch(keyPressed)
			{
				case Key_Backspace:
				case Key_Delete:
				{
					if(selectionStart != selectionEnd)
					{
						ClearSelection();
					}
					else
					{
						if(keyPressed == Key_Backspace && cursorPos > 0)
						{
							buffer.ClearRange(--cursorPos, 1);
							selectionStart = selectionEnd = cursorPos;

							if(changeCallback)
								changeCallback(buffer.CStr());
						}
						else if(keyPressed == Key_Delete && cursorPos < buffer.NumBytes())
						{
							buffer.ClearRange(cursorPos, 1);
							selectionStart = selectionEnd = cursorPos;

							if(changeCallback)
								changeCallback(buffer.CStr());
						}
					}
					break;
				}

				case Key_Left:
				case Key_Right:
				case Key_Home:
				case Key_End:
				{
					if(ctrl)
					{
						if(keyPressed == Key_Left)
						{
							while(cursorPos && MFIsWhite(buffer[cursorPos-1]))
								--cursorPos;
							if(MFIsAlphaNumeric(buffer[cursorPos-1]))
							{
								while(cursorPos && MFIsAlphaNumeric(buffer[cursorPos-1]))
									--cursorPos;
							}
							else if(cursorPos)
							{
								--cursorPos;
								while(cursorPos && buffer[cursorPos-1] == buffer[cursorPos])
									--cursorPos;
							}
						}
						else if(keyPressed == Key_Right)
						{
							while(cursorPos < buffer.NumBytes() && MFIsWhite(buffer[cursorPos]))
								++cursorPos;
							if(MFIsAlphaNumeric(buffer[cursorPos]))
							{
								while(cursorPos < buffer.NumBytes() && MFIsAlphaNumeric(buffer[cursorPos]))
									++cursorPos;
							}
							else if(cursorPos < buffer.NumBytes())
							{
								++cursorPos;
								while(cursorPos < buffer.NumBytes() && buffer[cursorPos] == buffer[cursorPos-1])
									++cursorPos;
							}
						}
						else if(keyPressed == Key_Home)
							cursorPos = 0;
						else if(keyPressed == Key_End)
							cursorPos = buffer.NumBytes();
					}
					else
					{
						if(keyPressed == Key_Left)
							cursorPos = (!shift && selectionStart != selectionEnd ? MFMin(selectionStart, selectionEnd) : MFMax(cursorPos-1, 0));
						else if(keyPressed == Key_Right)
							cursorPos = (!shift && selectionStart != selectionEnd ? MFMax(selectionStart, selectionEnd) : MFMin(cursorPos+1, buffer.NumBytes()));
						else if(keyPressed == Key_Home)
							cursorPos = 0;	// TODO: if multiline, go to start of line..
						else if(keyPressed == Key_End)
							cursorPos = buffer.NumBytes();	// TODO: if multiline, go to end of line...
					}

					if(shift)
						selectionEnd = cursorPos;
					else
						selectionStart = selectionEnd = cursorPos;

					break;
				}

				default:
				{
					bool caps = MFInput_GetKeyboardStatusState(KSS_CapsLock);
					int ascii = MFInput_KeyToAscii(keyPressed, shift, caps);

					if(ascii && (!maxLen || buffer.NumBytes() < maxLen-1))
					{
						// check character exclusions
						if(MFIsNewline(ascii) && type != ST_MultiLine)
							break;
						if(ascii == '\t' && type != ST_MultiLine)
							break;
						if(type == ST_Numeric && !MFIsNumeric(ascii))
							break;
						if(include)
						{
							if(include.FindChar(ascii) < 0)
								break;
						}
						if(exclude)
						{
							if(exclude.FindChar(ascii) >= 0)
								break;
						}

						int selMin = MFMin(selectionStart, selectionEnd);
						int selMax = MFMax(selectionStart, selectionEnd);
						int selRange = selMax - selMin;

						const uint16 wstr[] = { (uint16)ascii, 0 };
						char insert[5];
						MFString_CopyUTF16ToUTF8(insert, wstr);
						buffer.Replace(selMin, selRange, insert);
						cursorPos = selMin + 1;

						selectionStart = selectionEnd = cursorPos;

						if(changeCallback)
							changeCallback(buffer.CStr());
					}
					break;
				}
			}
		}
	}
}