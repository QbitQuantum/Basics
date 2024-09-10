void MyPoint::draw(CDC& dc)const
{
	dc.SetPixel(_x,_y,m_clr);
}