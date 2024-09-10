void Vector3F::rotateAroundAxis(const Vector3F& axis, float theta)
{
	if(theta==0) return;
	Vector3F ori(x,y,z);
	float l = ori.length();
	ori.normalize();
	
	Vector3F up = axis.cross(ori);
	up.normalize();
	
	Vector3F side = ori - axis*(axis.dot(ori));
	
	up *=side.length();
	
	ori += side*(cos(theta) - 1);
	ori += up*sin(theta);
	
	ori.normalize();
	x = ori.x*l;
	y = ori.y*l;
	z = ori.z*l;
}