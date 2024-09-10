Color PathTracer::diffuseBRDF(const Shape &obj, const Ray & ray, const Vector & hitpoint, const Vector & nl, int depth, int E) const
{
	/* Compute random reflection vector on hemisphere */
	double r1 = 2.0 * M_PI * drand48();
	double r2 = drand48();
	double r2s = sqrt(r2);

	Color col = obj.color;
	Vector e(0,0,0);

	/* Set up local orthogonal coordinate system u,v,w on surface */
	Vector w = nl;
	Vector u;

	if (fabs(w.x) > .1)
		u = Vector(0.0, 1.0, 0.0).Cross(w).Normalized();
	else
		u = (Vector(1.0, 0.0, 0.0).Cross(w)).Normalized();

	Vector v = w.Cross(u);

	/* Random reflection vector d */
	Vector d = (u * cos(r1) * r2s +
				v * sin(r1) * r2s +
				w * sqrt(1 - r2)).Normalized();

	if(sampleLight)
	{
		/* Explicit computation of direct lighting */
		for (int i = 0; i < numObjects; i++)
		{
			const Shape &cur_obj = *our_scene.get_shapes()[i];
			if (cur_obj.emission.x <= 0 && cur_obj.emission.y <= 0 && cur_obj.emission.z <= 0)
				continue; /* Skip objects that are not light sources */

			/* Randomly sample spherical light source from surface intersection */

			/* Set up local orthogonal coordinate system su,sv,sw towards light source */
			Vector cur_cent = cur_obj.get_position();
			Vector sw = (cur_cent - hitpoint).Normalized(); 

			Vector su;

			if (fabs(sw.x) > 0.1)
				su = Vector(0.0, 1.0, 0.0);
			else
				su = Vector(1.0, 0.0, 0.0);

			su = (sw.Cross(su)).Normalized();
			Vector sv = sw.Cross(su);

			// next event estimation
			/* Create random sample direction l towards spherical light source */
			double cos_a_max = sqrt(1.0 - cur_obj.radius * cur_obj.radius /
										  (hitpoint - cur_cent).Dot(hitpoint - cur_cent));

			double eps1 = drand48();
			double eps2 = drand48();
			double cos_a = 1.0 - eps1 + eps1 * cos_a_max;
			double sin_a = sqrt(1.0 - cos_a * cos_a);
			double phi = 2.0 * M_PI * eps2;
			Vector l = su * cos(phi) * sin_a +
					   sv * sin(phi) * sin_a +
					   sw * cos_a;
			l = l.Normalized();
			/* Shoot shadow ray, check if intersection is with light source */
			double t;
			int id = 0;
			if (Intersect(Ray(hitpoint,l), t, id) && id==i)
			{
				double omega = 2 * M_PI * (1 - cos_a_max);

				/* Add diffusely reflected light from light source; note constant BRDF 1/PI */
				e = e + cur_obj.emission * l.Dot(nl) * omega * M_1_PI;
			}
		}
		return obj.emission * E + obj.color.MultComponents(e) + col.MultComponents(Radiance(Ray(hitpoint, d), depth, 0));
	}
	else
		return obj.emission + col.MultComponents(Radiance(Ray(hitpoint, d), depth, 0));

	
	/* Return potential light emission, direct lighting, and indirect lighting (via
	   recursive call for Monte-Carlo integration */

}