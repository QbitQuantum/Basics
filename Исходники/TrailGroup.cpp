// Set the matrix to use to post process J2000 positions before storing in the trail
void TrailGroup::setJ2000ToTrailNative(const Mat4d& m)
{
	j2000ToTrailNative=m;
	j2000ToTrailNativeInverted=m.inverse();
}