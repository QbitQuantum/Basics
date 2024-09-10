PG_Rect PG_Rect::IntersectRect(const PG_Rect& p, const PG_Rect& c) {
	static int px0,py0,px1,py1;
	static int cx0,cy0,cx1,cy1;
	static int rx0,ry0,rx1,ry1;

	// fill in default (NULL) result rectangle
	PG_Rect result;

	// get coordinates of the rectangles
	px0 = p.my_xpos;
	py0 = p.my_ypos;
	px1 = p.my_xpos + p.my_width - 1;
	py1 = p.my_ypos + p.my_height - 1;

	cx0 = c.my_xpos;
	cy0 = c.my_ypos;
	cx1 = c.my_xpos + c.my_width - 1;
	cy1 = c.my_ypos + c.my_height - 1;

	// check if the rectangles intersect
	if((cx1 < px0) || (cx0 > px1) || (cy1 < py0) || (cy0 > py1))
		return result;

	// intersect x
	if(cx0 <= px0)
		rx0 = px0;
	else
		rx0 = cx0;

	if(cx1 >= px1)
		rx1 = px1;
	else
		rx1 = cx1;

	// intersect y
	if(cy0 <= py0)
		ry0 = py0;
	else
		ry0 = cy0;

	if(cy1 >= py1)
		ry1 = py1;
	else
		ry1 = cy1;

	// fill in result rect
	result.SetRect(
	    rx0,
	    ry0,
	    (rx1-rx0)+1,
	    (ry1-ry0)+1);

	return result;
}