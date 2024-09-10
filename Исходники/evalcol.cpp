// Returns the point to be shaded in object coordinates.
Point3 SContext::PObj(void)
{
	return Inverse(tmAfterWSM) * P();
}