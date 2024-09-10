void bta_sys_prompt(NPP instance, const char *error) {
	struct _bta_prompt_info *p = (struct _bta_prompt_info *)bta_malloc(sizeof(struct _bta_prompt_info)+strlen(error)+1);

	_bta_sys_info = p;
	p->pin = ((bta_info *)instance->pdata)->pin;
	p->parent= ((bta_info*)instance->pdata)->window;
	strcpy_s(p->error, strlen(error)+1, error);
	p->instance=instance;

	HINSTANCE hinstance = (HINSTANCE)GetWindowLong(p->parent, GWL_HINSTANCE);

	p->hfont = (HFONT)GetStockObject(ANSI_VAR_FONT); 
	p->cursor[0]=LoadCursor(NULL, IDC_ARROW);
	p->cursor[1]=LoadCursor(NULL, IDC_IBEAM);

	WNDCLASS wndclass;
	if( GetClassInfo(hinstance, L"BetterThanAdsPrompt", &wndclass)==0 ) {
		wndclass.lpszClassName=L"BetterThanAdsPrompt";
		wndclass.lpszMenuName=NULL;
		wndclass.cbClsExtra=0;
		wndclass.cbWndExtra=0;
		wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); 
		wndclass.hCursor=p->cursor[0];
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndclass.lpfnWndProc=_bta_sys_prompt_callback;
		wndclass.style=CS_HREDRAW|CS_VREDRAW;

		wndclass.hInstance=hinstance;

		if( !RegisterClass(&wndclass) ) {
			char ibuf[20];
			_itoa(GetLastError(),ibuf,10);
			logmsg("ERROR registering window class!\n   Error code: ");
			logmsg(ibuf);
			logmsg("\n");
			return;
		}
	}

	DWORD threadid;
	HANDLE promptThreadHandle = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)_bta_sys_prompt, p, 0, &threadid);
}