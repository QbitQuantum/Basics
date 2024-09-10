/**
Returns the plane through a, b and c.

@param a	The first vector in the plane
@param b	The second vector in the plane
@param c	The third vector in the plane
@return		As stated
*/
Plane_Ptr Antipenumbra::construct_clip_plane(const Vector3d& a, const Vector3d& b, const Vector3d& c)
{
	Vector3d v1 = b - a;
	Vector3d v2 = c - a;

	Vector3d n = v1.cross(v2);
	if(n.length_squared() < EPSILON) return Plane_Ptr();

	return Plane_Ptr(new Plane(n,a));
}