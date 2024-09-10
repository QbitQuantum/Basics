// Notify OS Input Method Editor of text input position (e.g. when using Japanese/Chinese inputs, otherwise this isn't needed)
static void ImImpl_ImeSetInputScreenPosFn( int x, int y ) {
	HWND hwnd = glfwGetWin32Window( g_Window );
	if ( HIMC himc = ImmGetContext( hwnd ) ) {
		COMPOSITIONFORM cf;
		cf.ptCurrentPos.x = x;
		cf.ptCurrentPos.y = y;
		cf.dwStyle = CFS_FORCE_POSITION;
		ImmSetCompositionWindow( himc, &cf );
	}
}