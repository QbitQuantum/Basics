int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	int argc;
	LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	char argv0[256];
	MSG msg;
	int fd;
	int code;
	fz_context *ctx;

	ctx = fz_new_context(NULL, NULL, FZ_STORE_DEFAULT);
	if (!ctx)
	{
		fprintf(stderr, "cannot initialise context\n");
		exit(1);
	}
	pdfapp_init(ctx, &gapp);

	GetModuleFileNameA(NULL, argv0, sizeof argv0);
	install_app(argv0);

	winopen();

	if (argc == 2)
	{
		wcscpy(wbuf, argv[1]);
	}
	else
	{
		if (!winfilename(wbuf, nelem(wbuf)))
			exit(0);
	}

	fd = _wopen(wbuf, O_BINARY | O_RDONLY, 0666);
	if (fd < 0)
		winerror(&gapp, "cannot open file");

	code = WideCharToMultiByte(CP_UTF8, 0, wbuf, -1, filename, sizeof filename, NULL, NULL);
	if (code == 0)
		winerror(&gapp, "cannot convert filename to utf-8");

	pdfapp_open(&gapp, filename, fd, 0);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	pdfapp_close(&gapp);

	return 0;
}