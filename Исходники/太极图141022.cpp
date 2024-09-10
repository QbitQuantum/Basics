void DrawTaiJi( HDC hdc, int x, int y, int radius,
			    COLORREF upperLeftColor, COLORREF lowerRightColor )
{
	HPEN hLowerRightPen = CreatePen( 0, 1, lowerRightColor );
	HPEN hUpperLeftPen = CreatePen( 0, 1, upperLeftColor );
	HBRUSH hLowerRightBrush = CreateSolidBrush( lowerRightColor );
	HBRUSH hUpperLeftBrush = CreateSolidBrush( upperLeftColor );

	//////////////////////////////////////////////////////////////////////////
	// 太极图外轮廓
	//////////////////////////////////////////////////////////////////////////
	SelectObject( hdc, hLowerRightPen );
	SelectObject( hdc, hLowerRightBrush );
	Chord( hdc, x-radius, y-radius, x+radius, y+radius, 
		x, y+radius, x, y-radius );

	SelectObject( hdc, hUpperLeftBrush );
	Chord( hdc, x-radius, y-radius, x+radius, y+radius, 
		x, y-radius, x, y+radius );

	//////////////////////////////////////////////////////////////////////////
	// 太极图上半部分
	//////////////////////////////////////////////////////////////////////////
	// 先用饼图将上面的圆的颜色画成上左方的配置颜色
	SelectObject( hdc, hUpperLeftBrush );
	SelectObject( hdc, hUpperLeftPen );
	Chord( hdc, x-radius/2, y-radius, x+radius/2, y, 
		x, y, x, y-radius );
	// 再用上左方配置颜色的弧将上面的圆弧画出来
	SelectObject( hdc, hLowerRightPen );
	Arc( hdc, x-radius/2, y-radius, (int)(x+radius/2), y, 
		x, y, x, y-radius );

	SelectObject( hdc, hLowerRightBrush );
	Ellipse( hdc, (int)(x-radius*0.2f), (int)(y-radius/2-radius*0.2f), 
			(int)(x+radius*0.2f), (int)(x-radius/2+radius*0.2f) );

	//////////////////////////////////////////////////////////////////////////
	// 太极图下半部分
	//////////////////////////////////////////////////////////////////////////
	SelectObject( hdc, hLowerRightBrush );
	Chord( hdc, x-radius/2, y, x+radius/2, y+radius, 
		x, y, x, y+radius);

	SelectObject( hdc, hUpperLeftBrush );
	Ellipse( hdc, (int)(x-radius*0.2f), (int)(y+radius/2-radius*0.2f), 
			(int)(x+radius*0.2f), (int)(y+radius/2+radius*0.2f) );

	// 删除所有对象
	DeleteObject( hUpperLeftPen );
	DeleteObject( hLowerRightPen );
	DeleteObject( hUpperLeftBrush );
	DeleteObject( hLowerRightBrush );
}