static void *SpVali_RayPath_Thread(void *tid_p)
{
	size_t tid = *((size_t *)tid_p);
	Zone *zp, *zone;
	SpPhys *pp, *zone_pp;
	size_t i, plane, izone;
	GeRay ray;
	double r, theta, phi, t;
	gsl_rng *rng = gsl_rng_alloc(gsl_rng_ranlux);

	gsl_rng_set(rng, (unsigned long)time(NULL));

	for(izone = 0, zone = Zone_GetMinLeaf(v_raypath_model.grid); zone; izone++, zone = Zone_AscendTree(zone)) {
		zone_pp = zone->data;

		/* Skip empty and non-leaf zones */
		if(!zone_pp->non_empty_leaf)
			continue;

		if((izone % Sp_MPISIZE) != Sp_MPIRANK)
			continue;
			
		if(((izone / Sp_MPISIZE) % Sp_NTHREAD) != tid)
			continue;

		#define NRAY 5000

		/* This samples a random number uniformly in the
		 * interval [0, 1) */
		#define RAND()\
			gsl_rng_uniform(rng)
		/* This samples a random number uniformly in the
		 * interval (0, 1) */
		#define PRAND()\
			gsl_rng_uniform_pos(rng)

		for(i = 0; i < NRAY; i++) {
			if(1) {
				ray = GeRay_Rand(rng, &zone->voxel);
			}
			else {
				Mem_BZERO(&ray);

				/* Init random ray origin */
				ray.e = zone->voxel.cen;
				r = GeRay_E(ray, 0);
				theta = PRAND() * PI;
				phi = RAND() * TWOPI;

				/* Convert to rectangular coordinates */
				GeRay_E(ray, 0) = r * sin(theta) * cos(phi);
				GeRay_E(ray, 1) = r * sin(theta) * sin(phi);
				GeRay_E(ray, 2) = r * cos(theta);

				/* Set random ray direction: first obtain direction in spherical
				 * coordinates then convert to rectangular coordinates */

				/* theta must be sampled with PRAND() or there may be a
				 * bias towards the theta=0 direction */
				theta = asin(2.0 * RAND() - 1.0) + 0.5 * PI;

				/* phi must be sampled with RAND() to avoid insufficient
				 * samples in the phi=0 direction */
				phi = PRAND() * TWOPI;

				/* Convert to rectangular coordinates */
				GeRay_D(ray, 0) = sin(theta) * cos(phi);
				GeRay_D(ray, 1) = sin(theta) * sin(phi);
				GeRay_D(ray, 2) = cos(theta);
			}

			zp = zone;

			/* Calculate radiative transfer along this direction */
			/* Propagate the ray through the cloud until we've
			 * reached the edge */
			while(zp) {
				/* Calculate path to next boundary */
				GeRay_TraverseVoxel(&ray, &zp->voxel, &t, &plane);

				/* Pointer to physical parameters associated with this zone */
				pp = zp->data;

				/* Do radiative transfer only if there are molecules in
				 * this zone */
				if(pp->non_empty_leaf) {
					zone_pp->ds += t;
				}

				/* Propagate ray to next position */
				ray = GeRay_Inc(&ray, t);

				/* Get next zone to traverse to */
				zp = Zone_GetNext(zp, plane, &ray);
			}
		}
		zone_pp->ds /= (double)NRAY;
	}

	return NULL;
}