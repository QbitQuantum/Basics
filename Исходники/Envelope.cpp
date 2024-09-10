/*public*/
bool
Envelope::intersection(const Envelope& env, Envelope& result) const
{
	if (isNull() || env.isNull() || ! intersects(env)) return false;

	double intMinX = minx > env.minx ? minx : env.minx;
	double intMinY = miny > env.miny ? miny : env.miny;
	double intMaxX = maxx < env.maxx ? maxx : env.maxx;
	double intMaxY = maxy < env.maxy ? maxy : env.maxy;
	result.init(intMinX, intMaxX, intMinY, intMaxY);
	return true;
}