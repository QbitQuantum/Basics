void CaptureScreen(char wnd_name[]){
	HWND hwnd;   
	hwnd = FindWindowA(NULL,wnd_name);

	//RECT wR,cR;
	//GetWindowRect(hwnd, &wR);
	//GetClientRect(hwnd, &cR);
	//printf("WINDOW RECT:{%04d, %04d, %04d, %04d};\nCLIENT RECT:{%04d, %04d, %04d, %04d};\n", wR.left,wR.top,wR.right, wR.bottom, cR.left,cR.top,cR.right, cR.bottom);

	CaptureScreen(hwnd);
}