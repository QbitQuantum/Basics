BOOL wbIsWBObj(void *pwbo, BOOL bShowErrors)
{
	if(!pwbo) {
		if(bShowErrors)
			wbError(__FUNCTION__, MB_ICONWARNING, "NULL WinBinder object");
		return FALSE;
	}

	// Is pwbo a valid memory address?

	if(IsBadReadPtr(pwbo, sizeof(WBOBJ))) {
		if(bShowErrors)
			wbError(__FUNCTION__, MB_ICONWARNING, "Invalid memory address");
//		printf("%d\n", pwbo);
		return FALSE;
	}

	// A Windows or menu handle is not a WinBinder object

	if(IsWindow(pwbo) || IsMenu(pwbo)) {
		if(bShowErrors)
			wbError(__FUNCTION__, MB_ICONWARNING, "Not a WinBinder object");
		return FALSE;
	}

	// Does it have a valid handle?

	{
		PWBOBJ pwboTest = wbMalloc(sizeof(WBOBJ));
		if(pwboTest) {
			CopyMemory(pwboTest, pwbo, sizeof(WBOBJ));

			if(!pwboTest->hwnd) {
				wbFree(pwboTest);
				if(bShowErrors)
					wbError(__FUNCTION__, MB_ICONWARNING, "NULL WinBinder object handle");
				return FALSE;
			}
			wbFree(pwboTest);
		}
	}

	if(IsMenu((HMENU)((PWBOBJ)pwbo)->hwnd))
		return TRUE;

	if(IsWindow((HWND)((PWBOBJ)pwbo)->hwnd))
		return TRUE;

	if(bShowErrors)
		wbError(__FUNCTION__, MB_ICONWARNING, "Invalid WinBinder object");

	return FALSE;
}