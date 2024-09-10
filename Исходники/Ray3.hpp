	/// Ray sphere intersection. Math referenced from:
	/// http://www.ccs.neu.edu/home/fell/CSU540/programs/RayTracingFormulas.htm
	inline float timeToIntersection(const Sphere& sphere) const
	{
		float a,b,c;
		a = dir.dot(dir);
		b = 2 * dir.dot( origin - sphere.center );
		c = sphere.center.dot( sphere.center ) +
			origin.dot(origin) -
			2 * sphere.center.dot(origin) - 
			sphere.radius * sphere.radius;
		float discr = b * b - 4 * a * c;
		if (discr < 0) {
			// No coliision
			return std::numeric_limits<float>::infinity();
		} else if (discr == 0) {
			// Grazing hit
			return (-b - sqrt(discr)) / (2*a);
		} else {
			// double hit, have to find the closest positive intersection
			float t = (-b - sqrt(discr)) / (2*a);
			if (t > 0) {
				return t;
			} else {
				t = (-b + sqrt(discr)) / (2*a);
				if (t > 0) {
					return t;
				} else {
					// only hits in negative time, ie, no hit.
					return std::numeric_limits<float>::infinity();
				}
			}
		}
	}