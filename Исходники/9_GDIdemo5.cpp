//-----------------------------------【Game_Paint( )函数】--------------------------------------
//	描述：绘制函数，在此函数中进行绘制操作
//--------------------------------------------------------------------------------------------------
VOID Game_Paint( HWND hwnd )
{
	//先贴上背景图
	SelectObject(g_mdc,g_hBackGround);
	BitBlt(g_hdc,0,0,WINDOW_WIDTH,WINDOW_HEIGHT,g_mdc,0,0,SRCCOPY);    //采用BitBlt函数在g_hdc中先贴上背景图

	//贴第一张人物图
	SelectObject(g_mdc,g_hCharacter1);
	TransparentBlt(g_hdc,0,WINDOW_HEIGHT-650,535,650,g_mdc,0,0,535,650,RGB(0,0,0));//透明色为RGB(0,0,0)

	//贴第二张人物图
	SelectObject(g_mdc,g_hCharacter2);
	TransparentBlt(g_hdc,500,WINDOW_HEIGHT-650,506,650,g_mdc,0,0,506,650,RGB(0,0,0));//透明色为RGB(0,0,0)
}