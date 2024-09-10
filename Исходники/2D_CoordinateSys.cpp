void	Draw2DCorSys(HWND hWnd,HDC hdc,P_2D_COORSYS p2DCoorSys)
{
	HPEN   m_COOR_Pen,mOldPen1,m_Grid_Pen,mOldPen2;
	RECT   mOPAixsRect,mHelpRect;
	HFONT  mTextFont1,mTextFont2,mOldFont;
	int	   iFontSize;
	TCHAR  chHelpString[200];
// 
	if((p2DCoorSys == NULL) || (hWnd == NULL) || (hdc == NULL))
 		return;

	m_COOR_Pen = CreatePen(PS_SOLID,2,RGB(0,0,0));
	mOldPen1 = (HPEN)SelectObject(hdc,m_COOR_Pen);

	//draw X axis
	MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,p2DCoorSys->shOP_YinScreen,NULL);
	LineTo(hdc,p2DCoorSys->shOP_XinScreen + p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio,
		p2DCoorSys->shOP_YinScreen);
	MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,p2DCoorSys->shOP_YinScreen,NULL);
	LineTo(hdc,p2DCoorSys->shOP_XinScreen - p2DCoorSys->shX_MinusAxisValue * p2DCoorSys->shPixelMapRatio,
		p2DCoorSys->shOP_YinScreen);

	//draw arrow
	MoveToEx(hdc,p2DCoorSys->shOP_XinScreen + p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio,
		p2DCoorSys->shOP_YinScreen,NULL);
	LineTo(hdc,p2DCoorSys->shOP_XinScreen + p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio - 5,
		p2DCoorSys->shOP_YinScreen - 5);
	MoveToEx(hdc,p2DCoorSys->shOP_XinScreen + p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio,
		p2DCoorSys->shOP_YinScreen,NULL);
	LineTo(hdc,p2DCoorSys->shOP_XinScreen + p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio - 5,
		p2DCoorSys->shOP_YinScreen + 5);

	//draw Y aixs
	MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,p2DCoorSys->shOP_YinScreen,NULL);
	LineTo(hdc,p2DCoorSys->shOP_XinScreen,p2DCoorSys->shOP_YinScreen
		- p2DCoorSys->shY_PlusAxisValue * p2DCoorSys->shPixelMapRatio);
	MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,p2DCoorSys->shOP_YinScreen,NULL);
	LineTo(hdc,p2DCoorSys->shOP_XinScreen,p2DCoorSys->shOP_YinScreen
		+ p2DCoorSys->shY_MinusAxisValue * p2DCoorSys->shPixelMapRatio);
	//draw arrow
	MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,p2DCoorSys->shOP_YinScreen
		- p2DCoorSys->shY_PlusAxisValue * p2DCoorSys->shPixelMapRatio,NULL);
	LineTo(hdc,p2DCoorSys->shOP_XinScreen - 5,p2DCoorSys->shOP_YinScreen
		- p2DCoorSys->shY_PlusAxisValue * p2DCoorSys->shPixelMapRatio + 5);
	MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,p2DCoorSys->shOP_YinScreen
		- p2DCoorSys->shY_PlusAxisValue * p2DCoorSys->shPixelMapRatio,NULL);
	LineTo(hdc,p2DCoorSys->shOP_XinScreen + 5,p2DCoorSys->shOP_YinScreen
		- p2DCoorSys->shY_PlusAxisValue * p2DCoorSys->shPixelMapRatio + 5);

	//display "+x"
	iFontSize = 40;
	mTextFont1 = CreateFont(iFontSize,0,0,0,FW_BOLD,
		0/*非斜体*/,0/*不带下划线*/,0,GB2312_CHARSET/*字符集*/,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,(LPCSTR)"Arial");
	mOldFont = (HFONT)SelectObject(hdc,mTextFont1);
	SetTextColor(hdc,RGB(0,0,255));

	mOPAixsRect.left = p2DCoorSys->shOP_XinScreen + p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio + 5;
	mOPAixsRect.right = mOPAixsRect.left + 40;
	mOPAixsRect.top = p2DCoorSys->shOP_YinScreen - 20;
	mOPAixsRect.bottom = p2DCoorSys->shOP_YinScreen +20;
	DrawText(hdc,"+x",2,&mOPAixsRect,DT_LEFT | DT_VCENTER);
	//display "+y"
	mOPAixsRect.left = p2DCoorSys->shOP_XinScreen - 20;
	mOPAixsRect.right = mOPAixsRect.left + 40;
	mOPAixsRect.bottom = p2DCoorSys->shOP_YinScreen
		- p2DCoorSys->shY_PlusAxisValue * p2DCoorSys->shPixelMapRatio +30;
	mOPAixsRect.top = mOPAixsRect.bottom - 40;
	DrawText(hdc,"+y",2,&mOPAixsRect,DT_LEFT | DT_VCENTER);

	
	//display help information.
	iFontSize = 15;
	mTextFont2 = CreateFont(iFontSize,0,0,0,FW_BOLD,
		0/*非斜体*/,0/*不带下划线*/,0,GB2312_CHARSET/*字符集*/,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,(LPCSTR)"Arial");
	mOldFont = (HFONT)SelectObject(hdc,mTextFont2);
	SetTextColor(hdc,RGB(255,0,0));


	mHelpRect.left = mTextRect.left;
	mHelpRect.top = mTextRect.top;
	mHelpRect.bottom = mHelpRect.top + 20;
	mHelpRect.right = mHelpRect.left + 300;

	sprintf(chHelpString,"X_OP:%d  Y_OP:%d\0",p2DCoorSys->shOP_XinScreen,p2DCoorSys->shOP_YinScreen);
	DrawText(hdc,chHelpString,strlen(chHelpString),&mHelpRect,DT_LEFT|DT_VCENTER);

	mHelpRect.top = mHelpRect.bottom;
	mHelpRect.bottom = mHelpRect.top + 20;
	sprintf(chHelpString,"Pixel Scale Ratio: 1:%d\0",p2DCoorSys->shPixelMapRatio);
	DrawText(hdc,chHelpString,strlen(chHelpString),&mHelpRect,DT_LEFT|DT_VCENTER);

	mHelpRect.top = mHelpRect.bottom;
	mHelpRect.bottom = mHelpRect.top + 20;
	sprintf(chHelpString,"Mouse_X:%d  Mouse_Y:%d\0",p2DCoorSys->shMouseXPos,p2DCoorSys->shMouseYPos);
	DrawText(hdc,chHelpString,strlen(chHelpString),&mHelpRect,DT_LEFT|DT_VCENTER);

	//draw grid.
	if(p2DCoorSys->bShowGrid)
	{
		int iTmp;

		m_Grid_Pen = CreatePen(PS_SOLID,1,RGB(255,0,0));
		mOldPen2 = (HPEN)SelectObject(hdc,m_Grid_Pen);
	
		for(iTmp = 1; iTmp <= p2DCoorSys->shX_PlusAxisValue; iTmp++)
		{
			MoveToEx(hdc,p2DCoorSys->shOP_XinScreen + iTmp * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen,NULL);
			LineTo(hdc,p2DCoorSys->shOP_XinScreen + iTmp * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen + p2DCoorSys->shY_MinusAxisValue * p2DCoorSys->shPixelMapRatio);
			MoveToEx(hdc,p2DCoorSys->shOP_XinScreen + iTmp * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen,NULL);
			LineTo(hdc,p2DCoorSys->shOP_XinScreen + iTmp * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen - p2DCoorSys->shY_MinusAxisValue * p2DCoorSys->shPixelMapRatio);
		}
		for(iTmp = 1; iTmp <= p2DCoorSys->shX_PlusAxisValue; iTmp++)
		{
			MoveToEx(hdc,p2DCoorSys->shOP_XinScreen - iTmp * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen,NULL);
			LineTo(hdc,p2DCoorSys->shOP_XinScreen - iTmp * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen + p2DCoorSys->shY_MinusAxisValue * p2DCoorSys->shPixelMapRatio);
			MoveToEx(hdc,p2DCoorSys->shOP_XinScreen - iTmp * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen,NULL);
			LineTo(hdc,p2DCoorSys->shOP_XinScreen - iTmp * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen - p2DCoorSys->shY_MinusAxisValue * p2DCoorSys->shPixelMapRatio);
		}
		for(iTmp = 1; iTmp <= p2DCoorSys->shY_PlusAxisValue; iTmp++)
		{
			MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,
				p2DCoorSys->shOP_YinScreen - iTmp * p2DCoorSys->shPixelMapRatio,NULL);
			LineTo(hdc,p2DCoorSys->shOP_XinScreen + p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen - iTmp * p2DCoorSys->shPixelMapRatio);
			MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,
				p2DCoorSys->shOP_YinScreen - iTmp * p2DCoorSys->shPixelMapRatio,NULL);
			LineTo(hdc,p2DCoorSys->shOP_XinScreen - p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen - iTmp * p2DCoorSys->shPixelMapRatio);
		}
		for(iTmp = 1; iTmp <= p2DCoorSys->shY_MinusAxisValue; iTmp++)
		{
			MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,
				p2DCoorSys->shOP_YinScreen + iTmp * p2DCoorSys->shPixelMapRatio,NULL);
			LineTo(hdc,p2DCoorSys->shOP_XinScreen + p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen + iTmp * p2DCoorSys->shPixelMapRatio);
			MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,
				p2DCoorSys->shOP_YinScreen + iTmp * p2DCoorSys->shPixelMapRatio,NULL);
			LineTo(hdc,p2DCoorSys->shOP_XinScreen - p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen + iTmp * p2DCoorSys->shPixelMapRatio);
		}


	}

	SelectObject(hdc,mOldPen1);
	SelectObject(hdc,mOldPen2);
	DeleteObject(m_COOR_Pen);
	DeleteObject(m_Grid_Pen);
	SelectObject(hdc,mOldFont);
	DeleteObject(mOldFont);
	return;
}