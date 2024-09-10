LRESULT CALLBACK HelperProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_ACTIVATE:
		if (LOWORD(wParam) != WA_INACTIVE) // Helper window got activated
			SetActiveWindow(hMirandaWnd);
		break;
	case WM_DESTROY:
		if (hWnd == hHelperWnd)
			hHelperWnd = NULL;
		else
			hDummyWnd = NULL;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}