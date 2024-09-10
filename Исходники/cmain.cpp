LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	const MARGINS objMargens = { 0, 0, Global::getInstance()->objMyWindow.intLargura, Global::getInstance()->objMyWindow.intAltura };

	switch (Message) {
		case WM_CREATE:
			DwmExtendFrameIntoClientArea(hWnd, &objMargens);
			break;

		case WM_DESTROY:
			PostQuitMessage(1);
			return 0;

		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);
			break;
	}

	return 0;
}