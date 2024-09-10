void  MyCircle::draw(CDC& dc)const
{
	if (enable)
	if (isPoint())
	{
		return ;
	}
	else
	{
		CPen pen(m_style,m_width,m_clr); 
		CPen *penOld = dc.SelectObject( &pen ); 
		dc.SelectStockObject(NULL_BRUSH);   
		
		int r = (int)sqrt((_x1-_x2)*(_x1-_x2)+(_y1-_y2)*(_y1-_y2));
		dc.Ellipse(_x1-r,_y1-r,_x1+r,_y1+r);

		dc.SelectObject(penOld);
		pen.DeleteObject();
	}
}