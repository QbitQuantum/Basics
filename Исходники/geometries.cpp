double Sphere::RayIntersect(Ray &ray, IntersectData *intersectData)
{
	double A = 1.0; // normalized ray vector
	double B = 2.0 * (ray.Vector().x * (ray.Point().x - center.x) + ray.Vector().y * (ray.Point().y - center.y) + ray.Vector().z * (ray.Point().z - center.z));
	double C = pow(ray.Point().x - center.x, 2.0) + pow(ray.Point().y - center.y, 2.0) + pow(ray.Point().z - center.z, 2.0) - radius * radius;
	double Det = B * B - 4.0 * A * C;

	if (Det >= 0.0)
	{
		double t = (-B - sqrt(Det)) / 2;

		if (t > 0.0)
		{
			if (intersectData)
			{
				Point3D contact = (Vector3D)ray.Point() + ray.Vector() * t;
				Vector3D normal = (Vector3D)contact - center;
				normal = normal.Normalize();

				intersectData->contact = contact;
				intersectData->normal = normal;
				intersectData->color = color;
			}

			return t;
		}

		t = (-B + sqrt(Det)) / 2;

		if (t > 0.0)
		{
			if (intersectData)
			{
				Point3D contact = (Vector3D)ray.Point() + ray.Vector() * t;
				Vector3D normal = (Vector3D)contact - center;
				normal = normal.Normalize();

				intersectData->contact = contact;
				intersectData->normal = normal;
				intersectData->color = color;

				return t;
			}
		}
	}

	return INFINITY;
}