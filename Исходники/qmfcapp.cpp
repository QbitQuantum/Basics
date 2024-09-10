/*!
    If there is no global QApplication object (i.e. qApp is null) this
    function creates a QApplication instance and returns true;
    otherwise it does nothing and returns false.

    The application installs an event filter that drives the Qt event
    loop while the MFC or Win32 application continues to own the event
    loop.

    Use this static function if the application event loop code can not be
    easily modified, or when developing a plugin or DLL that will be loaded
    into an existing Win32 or MFC application. If \a plugin is non-null then
    the function loads the respective DLL explicitly to avoid unloading from
    memory.

    \code
    BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpvReserved)
    {
	if (dwReason == DLL_PROCESS_ATTACH)
	    QMfcApp::pluginInstance(hInstance);

	return TRUE;
    }
    \endcode
*/
bool pluginInstance(Qt::HANDLE plugin)
{
    if (qApp)
	return FALSE;

    QT_WA({
	hhook = SetWindowsHookExW(WH_GETMESSAGE, QtFilterProc, 0, GetCurrentThreadId());
    }, {