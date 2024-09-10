void CCustomMonster::mk_rotation					(Fvector &dir, SRotation &R)
{
	// parse yaw
	Fvector DYaw;	
	DYaw.set							(dir.x,0.f,dir.z); 
	DYaw.normalize_safe					();
	clamp								(DYaw.x,-0.9999999f,0.9999999f);
	clamp								(DYaw.y,-0.9999999f,0.9999999f);
	clamp								(DYaw.z,-0.9999999f,0.9999999f);

	if ( DYaw.x >= 0 )
		R.yaw							= acosf(DYaw.z);
	else			
		R.yaw							= 2*PI-acosf(DYaw.z);

	// parse pitch
	dir.normalize_safe					();
	R.pitch								= -asinf(dir.y);
}