	// Taken from Irrlicht page
	btVector3 quatToEuler(const btQuaternion & quat)
	{
		btVector3 ret;
		btScalar w = quat.getW(), x = quat.getX(), y = quat.getY(), z = quat.getZ();
		float ws = w*w, xs = x*x, ys = y*y, zs = z*z;
		ret.setX(atan2f(2.0f*(y*z+x*w), -xs-ys+zs+ws));
		ret.setY(asinf(-2.0f*(x*z-y*w)));
		ret.setZ(atan2f(2.0f*(x*y+z*w), xs-ys-zs+ws));
		ret *= irr::core::RADTODEG;
		return ret;
	}