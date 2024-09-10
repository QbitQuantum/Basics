bool ventrilo_chat::Find()
{
	#ifdef OS_WINDOWS_
	std::cout << "bMumble: " << bMumble << std::endl;
	if (bMumble)
	{
		hwnd=FindWindowA("QWidget","Mumble -- DF Proximity Bot");
		char buf[255];
		do
		{
			if (hwnd)
			{
				GetWindowTextA(hwnd,buf,sizeof(buf));
				if (strncmp("Mumble -- ",buf,10) == 0)
				{
					hwndMessage=FindWindowExA(hwnd,NULL,"QWidget","qdwChat");
					if (hwndMessage)
					{
						HWND hTmp =FindWindowExA(hwndMessage,NULL,"QWidget","qleChat");
						if (!hTmp)
							std::cout << "Mumble chat box internal subwindow not found; using parent..." << std::endl;
						else
							hwndMessage=hTmp;
					}

					// TODO: make the chat window actually scrapable so we can give commands!
					hwndChat=FindWindowExA(hwnd,NULL,"QWidget","qdwLog");
					if (hwndChat)
						hwndChat=FindWindowExA(hwndChat,NULL,"QWidget","qteLog");
					if (hwndChat)
						hwndChat=FindWindowExA(hwndChat,NULL,"QWidget","qt_scrollarea_viewport");

					if (hwndMessage)
					{
						SetWindowText(hwnd,"Mumble -- DF Proximity Bot");
						return true;
					}
				}
			}
			std::cout << "!!" << buf << std::endl;
		} while ((hwnd=FindWindowExA(NULL,hwnd,"QWidget",NULL)));
	}
	else
	{
		// see if we marked one already
		hwnd=FindWindowA("#32770","Chat - DF Proximity Bot");
		do
		{
			if (hwnd)
			{
				HWND hwndParent=GetParent(hwnd);
				hwndMessage=FindWindowExA(hwnd,NULL,"Edit",NULL);
				hwndChat=FindWindowExA(hwnd,NULL,"RichEdit20A",NULL);
				hwndSend=FindWindowExA(hwnd,NULL,"Button","Send");
				hwndTTS=FindWindowExA(hwnd,NULL,"Button","Enable TTS");	
				hwndTimestamp=FindWindowExA(hwnd,NULL,"Button","Time stamp");	
				
				if (!hwndParent && hwndMessage && hwndChat && hwndSend && hwndTTS && hwndTimestamp)
				{
					SetWindowText(hwnd,"Chat - DF Proximity Bot");
					return true;
				}
			}
		} while ((hwnd=FindWindowExA(NULL,hwnd,"#32770","Chat")));
	}
	return false;
	#else
	return true;
	#endif
}