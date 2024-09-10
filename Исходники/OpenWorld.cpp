int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevinstance,
					 LPSTR lpszCmdParam,
					 int nCmdShow)
{
	if(FindWindow(szWindowClass, szTitle) != NULL) { //ÀÌ¹Ì ½ÇÇàÁßÀÌ¸é
		MessageBox(NULL, _TEXT("ÀÌ¹Ì OpenWorld°¡ ½ÇÇàÁßÀÔ´Ï´Ù."), szTitle, MB_OK);

		return 0;
	}

	ApplicationLogger.write("OpenWorld started.");
	ApplicationLogger.write("Application version: %s\n", VERSION);
	
	//ÅØ½ºÆ® ¿¡µ÷ ÄÁÆ®·Ñ proc º¯°æ
	GetClassInfo(NULL, "edit", &EditWndClass);

	EditOrigWndProc = (WNDPROC)EditWndClass.lpfnWndProc;
	EditWndClass.lpfnWndProc = EditWndProc;
	EditWndClass.hInstance = hInst;
	EditWndClass.lpszClassName = "Edit";

	//À©µµ¿ì Å¬·¡½º µî·Ï
	WndClassRegister(hInstance);
	RegisterClass((LPWNDCLASS)&EditWndClass);

	ApplicationLogger.write("Configure display option...");

	Option.OptionFile(".\\configure.ini");

	if(Option.getOptionByInt("OpenWorld", "window_mode") == -1) { //ini ÆÄÀÏÀÌ ´©¶ôµÇ¾ú°Å³ª ÇÊµå ¶Ç´Â ¿É¼Ç ¼³Á¤¿¡ ¿À·ù°¡ ÀÖ´Â°æ¿ì
		isWindowMode = 0;
		ApplicationLogger.write("Coudn't loaded window mode ini value - default set: 0");
	} else {
		isWindowMode = Option.getOptionByInt("OpenWorld", "window_mode");

		if(isWindowMode < 0 || isWindowMode > 1) { //0 ¶Ç´Â 1 ÀÌ¿ÜÀÇ °ªÀ¸·Î ¼³Á¤µÇÀÖ´Â °æ¿ì
			isWindowMode = 0;
			ApplicationLogger.write("window mode ini value has wrong value. default set: 0");
		}
	}

	ScreenWidth = Option.getOptionByInt("OpenWorld", "width");
	ScreenHeight = Option.getOptionByInt("OpenWorld", "height");

	if(ScreenWidth < 1 || ScreenHeight < 1) {
		ApplicationLogger.write("Display setting has wrong value. - default set: width=1024, height=768");
		MessageBox(NULL, "configure.ini ³» width ¶Ç´Â height °ªÀÌ Àß¸ø ¼³Á¤µÇ¾î ÀÖ½À´Ï´Ù.\n±âº»°ªÀÎ width=1024, height=768 ·Î Àç¼³Á¤ µÇ¾î ½ÇÇàµË´Ï´Ù.", "OpenWorld", MB_OK);

		Option.setOptionByInt("OpenWorld", "width", 1024);
		Option.setOptionByInt("OpenWorld", "height", 768);

		ScreenWidth = 1024;
		ScreenHeight = 768;
	}

	if(!InitWindowsForm(hInstance, nCmdShow, isWindowMode)) { //false ¸¦ ¸®ÅÏ¹ÞÀº °æ¿ì
		MessageBox(NULL, "OpenWorld Ã¢ÀÇ ÃÊ±âÈ­¿¡ ½ÇÆÐÇÏ¿´½À´Ï´Ù.", szTitle, MB_OK);

		return 0;
	}

	int Start_Time = 0, End_Time = 0, Frame_Time = 0;

	InitEngine();
	
	//ÀÎÆ®·Î
	while(Quit != 1) {
		MessageProcess();

		if(LogoIntro()) //·Î°í Ãâ·ÂÀÌ ³¡³ª¸é
			break;
	}

	//¸ÞÀÎ°ÔÀÓ
	while(Quit != 1) {
		MessageProcess();

		//¸ÞÀÎÇÚµéÀÏ¶§´Â ¹«Á¶°Ç IME¸¦ ¿µ¾î·Î ¼³Á¤(¾È±×·¯¸é ÇÑ±ÛÅ° ´­·ÁÀÖ¾î¼­ z °°Àº ½ºÅ³Å° ¾È³ª°¨)
		if(GetFocus() == hWndMain)
			ImmSetConversionStatus(ImmGetContext(hWndMain), IME_CMODE_ALPHANUMERIC, (DWORD)0);

		if(Frame_Time == 0)
			Frame_Time = 1;

		UpdateEngineStatus(Frame_Time);

		End_Time = clock();
		Frame_Time = End_Time - Start_Time;
		Start_Time = End_Time;
	}

	CloseEngine();

#ifdef DEBUG
	ShowWindow(hWndMain, SW_HIDE);
	system("pause");
#endif
	
	return 0;
}