void ShapeWindowFromBitmap(CImage &image,CWnd *pWnd,COLORREF keyColor)
{
	pWnd->MoveWindow(0,0,image.GetWidth(),image.GetHeight());
	if (!image.IsNull())
	{
		CRgn crRgn, crRgnTmp;
		crRgn.CreateRectRgn(0,0,0,0);
		for (int nY = 0; nY <= image.GetHeight(); nY++)
		{
			int nX = 0;
			do
			{
				while (nX <= image.GetWidth() && image.GetPixel(nX, nY) == keyColor)
					nX++;
				int iLeftX = nX;
				while (nX <= image.GetWidth() && image.GetPixel(nX, nY) != keyColor)
					++nX;
				crRgnTmp.CreateRectRgn(iLeftX, nY, nX, nY+1);
				crRgn.CombineRgn(&crRgn, &crRgnTmp, RGN_OR);
				crRgnTmp.DeleteObject();
			}while(nX < image.GetWidth());
			nX = 0;
		}
		pWnd->SetWindowRgn(crRgn,TRUE);
		crRgn.DeleteObject();
	}
}