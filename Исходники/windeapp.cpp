//
// Called at exit
//
void _USERENTRY CleanupApp()
{
	if ( hKeyboardHook != NULL )
		UnhookWindowsHookEx (hKeyboardHook);
	CleanupWindeu();
}