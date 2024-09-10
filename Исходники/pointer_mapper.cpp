bool PointerMapper::project_to_plane(Point3f& pt, Point3f& result, float& dist_to_plane)
{
    Ray ray = Ray(pt, direction_plane);

	float t;
    if (ray.intersects(plane, t))
    {
    	const float x = pt.x + t * direction_plane.x;
    	const float y = pt.y + t * direction_plane.y;
    	const float z = pt.z + t * direction_plane.z;
        result = Point3f(x, y, z);
        dist_to_plane = get_distance(result, pt);
        
        return true;
    }

    return false;
}