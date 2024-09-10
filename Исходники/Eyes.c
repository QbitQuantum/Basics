static TPoint computePupil (
    int		num,
    TPoint	mouse,
    const TRectangle *screen)
{
	double	cx, cy;
	double	dist;
	double	angle;
	double	dx, dy;
	double	cosa, sina;
	TPoint	ret;

	cx = EYE_X(num); dx = mouse.x - cx;
	cy = EYE_Y(num); dy = mouse.y - cy;
	if (dx == 0 && dy == 0);
	else {
		angle = atan2 ((double) dy, (double) dx);
		cosa = cos (angle);
		sina = sin (angle);
		dist = BALL_DIST;
		if (screen)
		{
		    /* use distance mapping */
		    double x0, y0, x1, y1;
		    double a[4];
		    x0 = screen->x - cx;
		    y0 = screen->y - cy;
		    x1 = x0 + screen->width;
		    y1 = y0 + screen->height;
		    a[0] = atan2(y0, x0);
		    a[1] = atan2(y1, x0);
		    a[2] = atan2(y1, x1);
		    a[3] = atan2(y0, x1);
		    if (AngleBetween(angle, a[0], a[1]))
		    {
			/* left */
			dist *= dx / x0;
		    }
		    else if (AngleBetween(angle, a[1], a[2]))
		    {
			/* bottom */
			dist *= dy / y1;
		    }
		    else if (AngleBetween(angle, a[2], a[3]))
		    {
			/* right */
			dist *= dx / x1;
		    }
		    else if (AngleBetween(angle, a[3], a[0]))
		    {
			/* top */
			dist *= dy / y0;
		    }
		    if (dist > BALL_DIST)
			dist = BALL_DIST;
		}
		if (dist > hypot ((double) dx, (double) dy)) {
			cx += dx;
			cy += dy;
		} else {
			cx += dist * cosa;
			cy += dist * sina;
		}
	}
	ret.x = cx;
	ret.y = cy;
	return ret;
}