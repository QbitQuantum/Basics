void CChineseChessDlg::DrawChessImage(int x, int y, HDC dc)
{
	HBITMAP hbmp;
	char name[3];
	char path[255];
	GetModuleFileName(NULL,path,255);
	(_tcsrchr(path,_T('\\')))[1] = 0;
	strcat(path,_T("\\Sourse\\"));
	if (chess[y][x].chessType != 0)
	{
		if (chess[y][x].isSelect)
		{
			strcat(path,_T("x"));
		}
		itoa(chess[y][x].chessType,name,10);
		strcat(path,name);
		strcat(path,_T(".bmp"));
		hbmp = (HBITMAP)LoadImage(AfxGetInstanceHandle(),path,
			IMAGE_BITMAP,50,50,LR_LOADFROMFILE);
		HBRUSH brush = CreatePatternBrush(hbmp); 
		HGDIOBJ hOld = SelectObject(dc,brush);
		RECT rec;
		rec.left = x * 50 ;
		rec.top = y * 50 ;
		rec.bottom = rec.top + 50;
		rec.right = rec.left + 50;
		FillRect(dc,&rec,brush);

		//╩ж╦╢т╜охв╢л╛
		SelectObject(dc, hOld);

		DeleteObject(brush);
		DeleteObject(hOld);
	}
}