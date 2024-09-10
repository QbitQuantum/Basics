// ray-sphere intersection test from Graphics Gems p.388
// **NOTE** There is a bug in this Graphics Gem.  If the origin
// of the ray is *inside* the sphere being tested, it reports the
// wrong intersection location.  This code has a fix for the bug.
bool  SBM_rayIntersectsSphere(const float *point,const float *direction,const float *_center,float radius,float &t)
{
  bool ret = false;

  NxVec3 rayOrigin(point);
  NxVec3 dir(direction);
  NxVec3 center(_center);

	// notation:
	// point E  = rayOrigin
	// point O  = sphere center

	NxVec3 EO = center - rayOrigin;
  NxVec3 V = dir;

  float dist2 = EO.x*EO.x + EO.y*EO.y + EO.z * EO.z;

  float r2 = radius*radius;

  // Bug Fix For Gem, if origin is *inside* the sphere, invert the
  // direction vector so that we get a valid intersection location.
  if ( dist2 < r2 )
    V*=-1;

	float v = EO.dot(V);

	float disc = r2 - (EO.magnitudeSquared() - v*v);

	if (disc > 0.0f)
	{
    t = sqrtf(disc);
		ret = true;
	}

	return ret;
}