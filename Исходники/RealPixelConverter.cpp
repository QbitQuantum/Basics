cRealPixelConverter::cRealPixelConverter(Real radiusx, Real radiusy)
{
	_changed_size_flag = TRUE;
	_fixed_aspect_flag = TRUE;
	if (!radiusx)
		radiusx = SMALL_REAL;
	if (!radiusy)
		radiusy = SMALL_REAL; //Never allow zeroes.
	_realradiusx = radiusx;
	_realradiusy = radiusy;
	_realcenterx = _realcentery = 0.0; //Default center at origin.
/* Force some numbers in to be safe, though normally you'll
call setPixelWindow again in the initial WM_SIZE with
the actual size of your active window. */
	setPixelWindow(800, 600);
}