//
// Destroys the control communication window.
//
static void destroy_control_window()
{
	DestroyWindow(cwindow);
	cwindow = NULL;
	UnregisterClass(klass.lpszClassName, klass.hInstance);
}