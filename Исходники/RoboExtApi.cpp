void	CalcNormal(CPoint3D v[3], CVector3D &out)
{
	CVector3D v1,v2;
	//static const int x = 0;
	//static const int y = 1;
	//static const int z = 2;

	// Calculate two vectors from the three points
	//v1.dx = v[0].x - v[1].x;
	//v1.dy = v[0].y - v[1].y;
	//v1.dz = v[0].z - v[1].z;
	v1=v[0]-v[1];

	//v2.dx = v[1].x - v[2].x;
	//v2.dy = v[1].y - v[2].y;
	//v2.dz = v[1].z - v[2].z;
	v2=v[1]-v[2];

	// Take the cross product of the two vectors to get
	// the normal vector which will be stored in out
	//out.dx = v1.dy*v2.dz - v1.dz*v2.dy;
	//out.dy = v1.dz*v2.dx - v1.dx*v2.dz;
	//out.dz= v1.dx*v2.dy - v1.dy*v2.dx;
	out = v1*v2;

	// Normalize the vector (shorten length to one)
	out.Normalize();
}