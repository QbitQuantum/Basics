//HHOOK m_hkeyboard;    //handler of keyboard hook
LRESULT CALLBACK LowLevelKeyboardProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	//Find the front window
	topWnd = GetForegroundWindow();
	
	PKBDLLHOOKSTRUCT kbstruct;
	kbstruct=(PKBDLLHOOKSTRUCT)lParam;
	DWORD dtemp = kbstruct->vkCode;//vkCode is the press buttom



	//we need to read keys configure from gameconfiguration.xml
	char ch_Temp = char(dtemp); /*- 0x41 + char('A');*/
	char ch_Corl;//doesn't take double key into account
	map<string , string>::iterator iter_Key = map_Key.begin();
	bool found = false;

	if(ch_Temp >= 96)
	{
		ch_Temp = ch_Temp - 96 + 48;
	}
	if(topWnd == m_hgame)
	{
		string str_Temp;
		str_Temp.clear();
		str_Temp.push_back(ch_Temp);
		if(WM_KEYDOWN == int(wParam))
		{
				/*int key_value = ch_Corl - char('A') + 0x41;
				keybd_event(key_value,0,0,0);*/
			switch (dtemp)
			{
				case 0x58:
					mouse_event(MOUSEEVENTF_LEFTDOWN , 0 , 0 , 0 , 0);
					return 1;
				case char('A'):
					mouse_event(MOUSEEVENTF_MOVE , -10 , 0 , 0 , 0);
					return 1;
				case char('S'):
					mouse_event(MOUSEEVENTF_MOVE , 10 , 0 , 0 , 0);
					return 1;
				case char('W'):
					mouse_event(MOUSEEVENTF_MOVE , 0 , 10 , 0 , 0);
					return 1;
				case char('E'):
					mouse_event(MOUSEEVENTF_MOVE , 0 , -10 , 0 , 0);
					return 1;
				default:
					break;	
			}
			
		}
		if(WM_KEYUP == int(wParam))
		{
			if(VK_RETURN == dtemp)
			{
				mouse_event(MOUSEEVENTF_LEFTUP , 0 , 0 , 0 , 0);
				return 1;
			}
		}
 			while(map_Key.end() != iter_Key)
			{
				if(0 == iter_Key->first.compare(str_Temp))
				{
					found = true;
					//ch_Corl = *(iter_Key->second.c_str());
					break;
				}
				iter_Key++;
			}

			if(found)
			{
				if(1 == iter_Key->second.length())
				{
					ch_Corl = *(iter_Key->second.c_str());
					if(WM_KEYDOWN == int(wParam))
					{
						int key_value = ch_Corl; /*- char('A') + 0x41;*/
						keybd_event(key_value,0,0,0);
						return 1;
					}
					if(WM_KEYUP == int(wParam))
					{
						int key_value = ch_Corl;/* - char('A') + 0x41;*/
						keybd_event(key_value,0,KEYEVENTF_KEYUP,0);
						return 1;
					}
				}
				else
				{
					int key_value;
					if(0 == string("UP").compare(iter_Key->second))
					{
						key_value = 0x26;
					}
					else if(0 == string("LEFT").compare(iter_Key->second))
					{
						key_value = 0x25;
					}
					else if(0 == string("RIGHT").compare(iter_Key->second))
					{
						key_value = 0x27;
					}
					else if(0 == string("DOWN").compare(iter_Key->second))
					{
						key_value = 0x28;
					}
					if(WM_KEYDOWN == int(wParam))
					{

						//int key_value = ch_Corl - char('A') + 0x41;
						keybd_event(key_value,0,0,0);
						return 1;
					}
					if(WM_KEYUP == int(wParam))
					{
						//int key_value = ch_Corl - char('A') + 0x41;
						keybd_event(key_value,0,KEYEVENTF_KEYUP,0);
						return 1;
					}
				}
			}


			
			

	}

	return CallNextHookEx(m_hkeyboard,nCode,wParam,lParam);
}