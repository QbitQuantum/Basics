void DrawRound(HDC hdc, const RECT &rect, int iStartPos, int iRound)
{
//	CPoint arrPoint[10] = {0};
//	
//	//start
//	arrPoint[0].x = rect.left;
//	arrPoint[0].y = rect.bottom - 1;
//
//	arrPoint[1].x = rect.left;
//	arrPoint[1].y = rect.top + 10;
//
//	
//	arrPoint[2].x = rect.left;
//	arrPoint[2].y = rect.top + 10;
//
//    //leftTop
//	arrPoint[3].x = rect.left;
//	arrPoint[3].y = rect.top;
//
//	arrPoint[4].x = rect.left + 10;
//	arrPoint[4].y = rect.top;
/////////////////////////////////////////////////////////////
//	arrPoint[5].x = rect.right - 11;
//	arrPoint[5].y = rect.top;
//
//	arrPoint[6].x = rect.right - 11;
//	arrPoint[6].y = rect.top;
//
//	//righttop
//	arrPoint[7].x = rect.right - 1;
//	arrPoint[7].y = rect.top;
//
//	arrPoint[8].x = rect.right - 1;
//	arrPoint[8].y = rect.top + 9;
//
//	arrPoint[9].x = rect.right - 1;
//	arrPoint[9].y = rect.bottom;
//
//	BYTE	barrType[10] = {PT_MOVETO, PT_LINETO, PT_BEZIERTO, PT_BEZIERTO, PT_BEZIERTO, PT_LINETO, PT_BEZIERTO, PT_BEZIERTO, PT_BEZIERTO, PT_LINETO};
//	PolyDraw(hdc, arrPoint, barrType, 10);


	CPoint arrPoint[6] = {0};

	switch (iStartPos)
	{
	case 3:
		//start
		arrPoint[0].x = rect.left;
		arrPoint[0].y = rect.bottom - 1;
	
		arrPoint[1].x = rect.left;
		arrPoint[1].y = rect.top + iRound;
	
		
		arrPoint[2].x = rect.left + iRound;
		arrPoint[2].y = rect.top;

		arrPoint[3].x = rect.right - iRound - 1;
		arrPoint[3].y = rect.top;

		arrPoint[4].x = rect.right - 1;
		arrPoint[4].y = rect.top + iRound;
	
		arrPoint[5].x = rect.right - 1;
		arrPoint[5].y = rect.bottom;
		break;
	case 1:
		arrPoint[0].x = rect.right - 1;
		arrPoint[0].y = rect.top;

		arrPoint[1].x = rect.right - 1;
		arrPoint[1].y = rect.bottom - iRound - 1;


		arrPoint[2].x = rect.right - iRound - 1;
		arrPoint[2].y = rect.bottom - 1;

		arrPoint[3].x = rect.left + iRound;
		arrPoint[3].y = rect.bottom - 1;

		arrPoint[4].x = rect.left;
		arrPoint[4].y = rect.bottom - iRound - 1;

		arrPoint[5].x = rect.left;
		arrPoint[5].y = rect.top - 1;
		break;
	}


		BYTE	barrType[6] = {PT_MOVETO, PT_LINETO, PT_LINETO, PT_LINETO, PT_LINETO, PT_LINETO};
		PolyDraw(hdc, arrPoint, barrType, 6);

}