BOOL WindowUtil_isToplevel(HWND hwnd) {
	BOOL toplevel;
	HWND parent;
	parent = GetAncestor(hwnd, GA_PARENT);

	/* According to MS: "A window that has no parent, or whose
	   parent is the desktop window, is called a top-level
	   window." See http://msdn2.microsoft.com/en-us/library/ms632597(VS.85).aspx. */
	toplevel = (!parent || parent == GetDesktopWindow());
	return toplevel;
}