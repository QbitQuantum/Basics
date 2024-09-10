void SpaceNavigatorPluginForm::WalkNavigatorRight( float step, Pnt3f& oldFrom, Pnt3f& oldAt, Vec3f& oldUp )
{
	Vec3f lv = oldFrom - oldAt;
	lv.normalize();

	Vec3f upn = oldUp;
	upn.normalize();

	Vec3f mv = lv - upn.dot(lv)*upn;
	mv.normalize();

	Vec3f sv = mv;
	sv.crossThis(upn);
	sv.normalize();

	oldFrom = oldFrom + step*sv;
	if (!_isOrbitMode)
		oldAt = oldAt + step*sv;

}