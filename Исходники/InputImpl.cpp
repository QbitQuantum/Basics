	String EventImpl::GetKeyName(Keyboard::Key key)
	{
		// http://www.ffuts.org/blog/mapvirtualkey-getkeynametext-and-a-story-of-how-to/
		int vk = vKeys[key];
		unsigned int code = MapVirtualKeyW(vk, 0) << 16;

		///FIXME: Liste complète ?
		switch (vk)
		{
			case VK_ATTN:
			case VK_DOWN:
			case VK_DECIMAL:
			case VK_DELETE:
			case VK_DIVIDE:
			case VK_END:
			case VK_HOME:
			case VK_INSERT:
			case VK_LEFT:
			case VK_LWIN:
			case VK_OEM_1:
			case VK_OEM_2:
			case VK_OEM_3:
			case VK_OEM_4:
			case VK_OEM_5:
			case VK_OEM_6:
			case VK_OEM_7:
			case VK_OEM_CLEAR:
			case VK_OEM_COMMA:
			case VK_OEM_MINUS:
			case VK_OEM_PERIOD:
			case VK_OEM_PLUS:
			case VK_PAUSE:
			case VK_NEXT:
			case VK_NUMLOCK:
			case VK_PRIOR:
			case VK_RIGHT:
			case VK_RWIN:
			case VK_UP:
				code |= 0x1000000; // 24ème bit pour l'extension
				break;
		}

		wchar_t keyName[20]; // Je ne pense pas que ça dépassera 20 caractères
		if (!GetKeyNameTextW(code, &keyName[0], 20))
			return "Unknown";

		return String::Unicode(keyName);
	}