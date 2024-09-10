void clearScreen(){
	HDC hdc = GetWindowDC(hwnd);
	RECT rect = {155, 65, 300, 92};
	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
	FillRect(hdc, &rect, brush);				
	DeleteObject(brush);
}