HWND findLastParent(HWND window, bool (*criterium)(HWND)) {
	HWND ancestor = window;
	HWND match = NULL;
	while (ancestor && ancestor != INVALID_HANDLE_VALUE) {
		DEBUGLOG("Current ancestor is 0x%X", ancestor);
		if (criterium(ancestor)) {
			DEBUGLOG("We like your style; storing candidate 0x%X", ancestor);
			match = ancestor;
		}
		ancestor = GetAncestor(ancestor, GA_PARENT);
	}
	return match;
}