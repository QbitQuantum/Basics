void Map10umToLogical(HDC hDC, RECT & rect)
{
	POINT * pPoint = (POINT *) & rect;

	// convert from 0.01 mm to pixels for current device
	for (int i=0; i<2; i++)
	{	
		int       t = GetDeviceCaps(hDC, HORZSIZE) * 100; 
		pPoint[i].x = ( pPoint[i].x * GetDeviceCaps(hDC, HORZRES) + t/2 ) / t;

		   	      t = GetDeviceCaps(hDC, VERTSIZE) * 100;
		pPoint[i].y = ( pPoint[i].y * GetDeviceCaps(hDC, VERTRES) + t/2 ) / t;
	}

	// convert to logical coordinate space
	DPtoLP(hDC, pPoint, 2);
}