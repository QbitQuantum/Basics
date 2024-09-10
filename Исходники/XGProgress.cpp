void XGProgress::DrawBar(XGDraw &draw)
{
	XRect r = GetContentRect();	
	short x;
	long min,max,val;
	XRect s;
	
	draw.Draw3DRect(r,KXGEFrame);
	::InsetRect(&r,1,1);
	
	min = fMin/fScale;
	max = fMax/fScale;
	val = fValue/fScale;
	
	if ((r.right - r.left) > (r.bottom - r.top)) {
		x = ((r.right - r.left) * (val - min)) / (max - min);
		
		s = r;
		s.left = r.right = x;
	} else {
		x = ((r.bottom - r.top) * (val - min)) / (max - min);
		
		s = r;
		s.top = r.bottom = x;
	}
	
	if (!::EmptyRect(&s)) draw.Draw3DRect(s,KXGEBackground);
	if (!::EmptyRect(&r)) {
		draw.FillRect(r,KXGColorBtnShadow);
	}
}