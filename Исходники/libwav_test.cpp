int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);




	beats = new bool[bd.length()];
	int ttt = 0;
	while (bd.hasNext())
	{
		double t = bd.next();
		//std::wstringstream wss;
		//wss << t;
		//MessageBox(0, wss.str().c_str(), _T(""), 0);
		beats[ttt++] = t;
		//beats[ttt++] = bd.next();
	}
	
	//int count = 0;
	//for (int i = 0; i < bd.length(); i++)
	//{
	//	if (beats[i]) count++;
	//	else if (count > 0)
	//	{
	//		if (count % 2 == 0) count--;
	//		if (count == 0) continue;

	//		for (int j = i - count; j < i; j++)
	//		{
	//			if (i - j == count / 2) beats[j] = true;
	//			else beats[j] = false;
	//		}

	//		count = 0;
	//	}
	//	else count = 0;
	//}

	std::ofstream out("sound.wav.analyze", std::ios::out);
	for (int i = 0; i < bd.length(); i++)
	{
		out << i * bd.getPrecision() << "\t" << beats[i] << std::endl;
	}
	out.close();

	bd.release();
	w.reset();

	FILE *f = fopen("sound.wav", "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);
	BYTE* raw = new BYTE[fsize];
	fread(raw, 1, fsize, f);
	fclose(f);
	Wave tmp(std::string((char*)raw, fsize), Wave::RAW);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;


	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LIBWAV_TEST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LIBWAV_TEST));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	GdiplusShutdown(gdiplusToken);
	return (int) msg.wParam;
}