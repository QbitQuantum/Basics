void CDitheringView::OnOrdered4()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDitheringDoc* pDoc = GetDocument();
	CClientDC dc(this);
	int ditherMatrix[4][4] = {0, 8, 2, 10, 12, 4, 14, 6, 3, 11, 1, 9, 15, 7, 13, 5};
	CDC memDC;
	memDC.CreateCompatibleDC( &dc );
	 
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap( &dc, pDoc->width, pDoc->height);
	memDC.SelectObject( &bitmap );

	int i, j, x, y, k = 0;

	for(i = 0; i < pDoc->pixel.GetSize(); i++){
		pDoc->ditherPixel.Add(RGBtoGray(pDoc->pixel[i]));
		pDoc->ditherLevel.Add(dither2Leveling(RGBtoGray(pDoc->pixel[i])));
	}
	
	for(i = 0; i < pDoc->height; i++){
		for(j = 0; j < pDoc->width; j++){
			x = i % 4;
			y = j % 4;

			if(pDoc->ditherLevel[k] > ditherMatrix[x][y]){
				memDC.SetPixel(i, j, pDoc->ditherPixel[k]);
			}else{
				memDC.SetPixel(i, j, RGB(255, 255, 255));
			}
			k++;
		}
	}
	
	dc.BitBlt(0, 0, pDoc->width, pDoc->height, &memDC, 0, 0, SRCCOPY);
}