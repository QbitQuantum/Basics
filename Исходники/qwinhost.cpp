/*!
    Destroys the QWinHost object. If the hosted Win32 window has not
    been set explicitly using setWindow() the window will be
    destroyed.
*/
QWinHost::~QWinHost()
{
	if (wndproc)
	{
#if defined(GWLP_WNDPROC)
		QT_WA({ SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)wndproc); },
		      { SetWindowLongPtrA(hwnd, GWLP_WNDPROC, (LONG_PTR)wndproc); })