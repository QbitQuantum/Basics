INT LcD3D_DrawTextBackbuffer(PDEV pDev, INT X, INT Y, LPCTSTR Text, DWORD _color)
{
	HDC hDC=0;
	LPDIRECT3DSURFACE9 Surface;

	if(FAILED(pDev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &Surface)))
		return -1;

	Surface->GetDC(&hDC);

	if(NULL != hDC)
	{
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, _color);
		TextOut(hDC, X, Y, Text, strlen(Text));

		Surface->ReleaseDC(hDC);
	}

	Surface->Release(); //해제한다.


	return 0;
}