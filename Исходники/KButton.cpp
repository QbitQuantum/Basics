KButton::~KButton()
{
	if(hwnd!=0)
		CloseWindow(hwnd);
}