static bool test_rect(const RECT * rc) {
	RECT clip = {};
	if (EnumDisplayMonitors(NULL,NULL,__MonitorEnumProc,(LPARAM)&clip)) {
		const LONG sanitycheck = 4;
		const LONG cwidth = clip.right - clip.left;
		const LONG cheight = clip.bottom - clip.top;
		
		const LONG width = rc->right - rc->left;
		const LONG height = rc->bottom - rc->top;

		if (width > cwidth * sanitycheck || height > cheight * sanitycheck) return false;
	}
	
	return MonitorFromRect(rc,MONITOR_DEFAULTTONULL) != NULL;
}