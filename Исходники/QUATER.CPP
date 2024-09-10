void quater::toAxisAngle(vector3& axis, double& angle) const
{
/*

#ifdef USE_D3DFUNC
	buggy.-.-
	D3DXQuaternionToAxisAngle(*this, axis, &angle);	
#else
	*/
	vector3 log;
	log.ln(*this);
	axis.normalize(log);
	angle=log.length()*2.f;

//#endif
}