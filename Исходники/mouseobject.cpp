/* Project the cursor's current location onto the plane specified by the normal
 * vector 'normal' and a perpendicular distance 'dist' from the origin.
 */
vector
mousebase::project1( vector normal, double dist)
{
	double ndc = normal.dot(cam) - dist;
	double ndr = normal.dot(get_ray());
	double t = -ndc / ndr;
	vector v = cam + get_ray()*t;
	return v;
}