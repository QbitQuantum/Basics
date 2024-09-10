HWND notepad(LPCSTR name) {
	char filename[1024], title[1024];
	FILE *f=0x0;
	sprintf_s(filename, 1024, "%s.txt", name);
	DWORD rc = fopen_s(&f, filename, "w");
	if(rc!=0) {
		printf("[-] failed to create temporary text file\n");
	}
	fclose(f);
	HINSTANCE inst = ShellExecuteA(0x0, "open", "notepad.exe", filename, 0x0, SW_SHOW);
	if(inst < (HINSTANCE)33) {
		printf("[-] failed to start notepad\n");
	}
	while(1) {
	sprintf_s(title, 1024, "%s - Notepad", name);
	HWND hwnd = FindWindowA(0x0, title);
	if(hwnd) {
		return hwnd;
	}
	sprintf_s(title, 1024, "%s.txt - Notepad", name);
	hwnd = FindWindowA(0x0, title);
	if(hwnd) {
		//printf("[-] failed to retrieve handle to notepad window\n");
		//return 0x0;
		return hwnd;
	}
	}
	return 0x0;
}