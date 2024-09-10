int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	// TODO: Place code here.
	MSG msg;

	//CoInitialize(0); // for Shell Icons

	// Initialize global strings
	htmlayout::window::register_class(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}


	// Main message loop:
	while (GetMessageW(&msg, NULL, 0, 0))
	{
		// execute asynchronous tasks in GUI thread.
		htmlayout::queue::execute();

		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return msg.wParam;
}