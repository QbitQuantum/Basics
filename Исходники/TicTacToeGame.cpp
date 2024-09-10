void TicTacToeGame::DrawIconCentered(HDC hdc, RECT *pRect, HICON hIcon)
{
	const int ICON_SIZE = 32;

	if (NULL != pRect)
	{
		int left = pRect->left + ((pRect->right - pRect->left) - ICON_SIZE) / 2;
		int top = pRect->top + ((pRect->bottom - pRect->top) - ICON_SIZE) / 2;
		DrawIcon(hdc, left, top, hIcon);
	}
}