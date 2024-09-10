void RectangularLight::getIrradianceSamples(Vec3f point, const Scene* scene, vector<LightRay>& result, float time) {
	// Draw new samples
	std::vector<Vec2f> drawnPoints(nSamples);
	randomSampler->generateSamples(nSamplesSqrt, drawnPoints);
	
	Color3f sum = Color3f(0);
	for (unsigned int i = 0; i < nSamples; i++) {
		// Warp and rotate samples
		Vec3f warpedPoint = Vec3f(size.x*drawnPoints[i].x, 0, size.y*drawnPoints[i].y);
		
		Vec3f difference = point - (warpedPoint + minPosition);
		float distance = difference.length();

		LightRay lr;
		Ray r;
		lr.direction = difference / distance;
		r.d = lr.direction;
		r.o = warpedPoint + minPosition;
		r.tMax = distance - r.tMin;
		r.time = time;

		// Check for intersection
		for (unsigned int k = 0; k < scene->shapes.size(); k++)
			scene->shapes[k]->intersect(&r);

		//if ray hit something then it does not contribute
		if (r.hit.shape == 0) {
			float pdf = 1/(size.x*size.y);
			lr.radiance = power * std::max(0.f,dot(lr.direction, Vec3f(0,-1,0))) / (2*static_cast<float>(M_PI)*pow(distance, 2));
		} else
			lr.radiance = Color3f(0);
		result.push_back(lr);
	}
}