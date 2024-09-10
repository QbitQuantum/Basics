static HWND clone_window(HWND hWnd, LPVOID lpParam)
{
	int count;

	SetLastError(NO_ERROR);

	DWORD dwExStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
	WIN32_CHK(GetLastError() == NO_ERROR);

	WCHAR lpClassName[100] = L"";
	count = GetClassNameW(hWnd, lpClassName, sizeof(lpClassName));
	WIN32_CHK(count != 0);

	WCHAR lpWindowName[100] = L"";
	count = GetWindowTextW(hWnd, lpWindowName, sizeof(lpWindowName));
	WIN32_CHK(count != 0);

	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
	WIN32_CHK(GetLastError() == NO_ERROR);

	RECT rect;
	GetWindowRect(hWnd, &rect);
	WIN32_CHK(GetLastError() == NO_ERROR);

	HWND hWndParent = (HWND)GetWindowLongPtr(hWnd, GWLP_HWNDPARENT);
	WIN32_CHK(GetLastError() == NO_ERROR);

	HMENU hMenu = GetMenu(hWnd);
	WIN32_CHK(GetLastError() == NO_ERROR);

	HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
	WIN32_CHK(GetLastError() == NO_ERROR);

	HWND hwndCloned = CreateWindowExW(
	        dwExStyle,
	        lpClassName,
	        lpWindowName,
	        dwStyle,
	        rect.left,
	        rect.top,
	        rect.right - rect.left,
	        rect.bottom - rect.top,
	        hWndParent,
	        hMenu,
	        hInstance,
	        lpParam);

	WIN32_CHK(hwndCloned != NULL);

	return hwndCloned;
}