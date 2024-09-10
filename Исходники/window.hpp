void Window::getClientRect(LPRECT rect) const
{
	CHECK_INIT();
	
	if(!rect)
		throw INVALID_ARGUMENT_EXCEPTION_1("rect");
	
	WINDOWINFO wi;
	if(!GetWindowInfo(hwnd(), &wi))
		throw WIN32EXCEPTION_1("GetWindowInfo");
	
	memcpy(rect, &wi.rcClient, sizeof(RECT));
}