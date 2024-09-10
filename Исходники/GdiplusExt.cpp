GraphicsPath* GdipCreateRoundRect( RectF& rect, int nRadiusLT, int nRadiusRT, int nRadiusRB, int nRadiusLB )
{
	GraphicsPath roundRect;
	if( nRadiusLT == 0 )
		roundRect.AddLine( rect.GetLeft(), rect.GetTop(), rect.GetRight() - (nRadiusRT<<1), rect.GetTop() );
	else
		roundRect.AddArc( RectF(rect.GetLeft(), rect.GetTop(), (float)(nRadiusLT<<1), (float)(nRadiusLT<<1)), 180, 90 );

	if( nRadiusRT == 0 )
		roundRect.AddLine( rect.GetRight(), rect.GetTop(), rect.GetRight(), rect.GetBottom()-(float)(nRadiusRB<<1) );
	else
		roundRect.AddArc( RectF(rect.GetRight() - (float)(nRadiusRT<<1), rect.GetTop(), (float)(nRadiusRT<<1), (float)(nRadiusRT<<1)), 270, 90 );

	if( nRadiusRB == 0 )
		roundRect.AddLine( rect.GetRight(), rect.GetBottom(), rect.GetLeft()-(float)(nRadiusLB<<1), rect.GetBottom() );
	else
		roundRect.AddArc( RectF(rect.GetRight() - (float)(nRadiusRB<<1), rect.GetBottom() -(float)(nRadiusRB<<1), (float)(nRadiusRB<<1), (float)(nRadiusRB<<1)), 0, 90 );

	if( nRadiusLB == 0 )
		roundRect.AddLine( rect.GetLeft(), rect.GetBottom(), rect.GetLeft(), rect.GetTop()-(float)(nRadiusLT<<1) );
	else
		roundRect.AddArc( RectF(rect.GetLeft(), rect.GetBottom() -(float)(nRadiusLB<<1), (float)(nRadiusLB<<1), (float)(nRadiusLB<<1)), 90, 90 );

	roundRect.CloseFigure();

	return roundRect.Clone();
}