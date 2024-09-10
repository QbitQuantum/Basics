RGB SubsurfacePathtracer::trace(Ray p_ray, Vector3d cameraPos, int p_depth) {

	RGB radiance(0,0,0);
	RGB localRadiance(0,0,0);
	RayIntersection nearestRayInt;
	p_depth++;
	
	bool intersected = false;

	if(scene->kdTree == NULL) {
		intersected = p_ray.nearestIntersection(scene->getObjects(), scene->getObjectCount(), &nearestRayInt);
	} else {
		intersected = scene->kdTree->nearestIntersection(&p_ray, &nearestRayInt);
	}

	if(intersected) {
		if(!(nearestRayInt.object->getShader()->isLight() && p_ray.getDiffuse())) {
			//local ilumination:
			Vector3d viewVec = cameraPos - nearestRayInt.point;
			viewVec.normalize();
			localRadiance = nearestRayInt.object->getShader()->getDiffuseRadiance(nearestRayInt.object, nearestRayInt.point, nearestRayInt.normal, nearestRayInt.uv, viewVec, scene);

			radiance = localRadiance;

			if(nearestRayInt.object->getShader()->hasSubsurface()) {
				radiance = radiance + subsurface(&nearestRayInt, &p_ray);
				//return subsurface(&nearestRayInt, &p_ray);
			}

			int outVecsCount = 0;
			RGB indirectRadiance;

			if(p_depth == 1) {
				for(int i = 0; i < 5; i++) {
					if(p_depth < maxDepth) {
						Ray outRays[10];
						RGB values[10];
						outVecsCount = nearestRayInt.object->getShader()->getBRDFSampledRays(nearestRayInt.object, nearestRayInt.point, nearestRayInt.normal, nearestRayInt.uv, viewVec, p_ray.getDir(), outRays, values);
						
						for(int s = 0; s < outVecsCount; s++) {
							Ray ray = outRays[s];
							indirectRadiance = indirectRadiance + (trace(ray, cameraPos, p_depth) * values[s]) ;
						}
					}

					indirectRadiance;
				}

				indirectRadiance = indirectRadiance / 5;
			} else {
				if(p_depth < maxDepth) {
					Ray outRays[10];
					RGB values[10];
					outVecsCount = nearestRayInt.object->getShader()->getBRDFSampledRays(nearestRayInt.object, nearestRayInt.point, nearestRayInt.normal, nearestRayInt.uv, viewVec, p_ray.getDir(), outRays, values);
					
					for(int s = 0; s < outVecsCount; s++) {
						Ray ray = outRays[s];
						indirectRadiance = indirectRadiance + (trace(ray, cameraPos, p_depth) * values[s]) ;
					}
				}	
			}

			if(outVecsCount > 0) {
				radiance =  radiance + indirectRadiance;
			}

		}
	} else if(scene->getBackground() != NULL) {
		radiance = scene->getBackground()->getRadianceAt(p_ray.getPoint(), p_ray.getPointAt(FAR_AWAY));
	}

	return radiance;
}