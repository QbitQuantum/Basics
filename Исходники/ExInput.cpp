DWORD __fastcall ExInput::GameInput(wchar_t* wMsg)
{
	static char In[400], *str, *tok;
	Misc::WideToChar(In, wMsg);
	str = strtok_s(In, " ", &tok);


	if (_stricmp(str, "#r") == 0)
	{
		str = strtok_s(NULL, " ", &tok);
		CreateThread(0, 0, &ExOOG::Rejoin, str, 0, 0);
		return -1;
	}
#if _DEBUG
	if (_stricmp(str, "#icon") == 0)
	{
		ExEventTextMsg hEvent;
		hEvent.Argument = 0;
		hEvent.MsgType = EXEVENT_TEXTMSG;
		hEvent.Color = COL_RED;
		hEvent.wX = -1;
		hEvent.wY = 50;
		hEvent.Sound = 10;
		hEvent.P_A6 = 0xA6;
		int Dmg = 10000;
		sprintf_s(hEvent.szMsg, 255, "%d !", Dmg);
		hEvent.PacketLen = 0xE + strlen(hEvent.szMsg) + 1;

		static int eLen = 0;
		D2Funcs.D2NET_ReceivePacket(&eLen, (BYTE*)&hEvent, hEvent.PacketLen);

		return -1;
	}
	if (_stricmp(str, "#icon2") == 0)
	{
		ExEventDownload pEvent = {};
		pEvent.P_A6 = 0xA6;
		pEvent.MsgType = EXEVENT_DOWNLOAD;
		pEvent.bExec = 0;
		strcpy_s(pEvent.szURL, 255, "http://download.thinkbroadband.com/1GB.zip");
		if (pEvent.szURL[0])
			pEvent.PacketLen = 14 + strlen(pEvent.szURL) + 1;
		else
			pEvent.PacketLen = 15;

		static int eLen = 0;
		D2Funcs.D2NET_ReceivePacket(&eLen, (BYTE*)&pEvent, pEvent.PacketLen);

		return -1;
	}
	static exId test_ui[100] = { exnull_t };
	if (strcmp(In, "#t1") == 0)
	{

		for (int i = 0; i < 100; ++i) {
			wostringstream str2;
			str2 << "Tescik " << i;
			test_ui[i] = gExGUI->add(new ExTextBox(10, 10 +(15*i), COL_WHITE, 5, str2.str(), NULL));
		}
		return -1;
	}
	if (strcmp(In, "#t2") == 0)
	{
		ExDownload::ShowHide();
	}
	if (strcmp(In, "#t3") == 0)
	{ 
		auto test = blizz_unique_ptr<char>((char*)D2ASMFuncs::D2WIN_ReadFileFromMPQ("DATA\\LOCAL\\FONT\\LATIN\\README.TXT", NULL, NULL));
		DEBUGMSG("Read text with data: %s", test)
	}