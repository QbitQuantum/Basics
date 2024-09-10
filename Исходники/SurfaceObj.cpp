Vec3f SurfaceObj::computeFaceNormal(Vec3f p1, Vec3f p2, Vec3f p3)
{
	Vec3f vector1, vector2;
	Vec3f normal;
	vector1=p2-p1; 
	vector2=p3-p1; 
	normal = vector1.cross(vector2);
	normal.normalize();
	return normal;
}