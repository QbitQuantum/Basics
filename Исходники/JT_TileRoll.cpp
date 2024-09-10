void JT_TileRoll::_validate(bool)
{
	// Figure out the integer translations. Floor(x+.5) is used so that
	// values always round the same way even if negative and even if .5
	dx = int(floor(x - x0 + .5));
	dy = int(floor(y - y0 + .5));
	
	copy_info();
	
	// create the transformation matrix for the GUI:
	matrix_.translation(x, y);
	
	// enforce the same bbox
	Box b(input0().info().x(), input0().info().y(), input0().info().r(), input0().info().t());
	info_.intersect(b);
}