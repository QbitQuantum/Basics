void CaptureParticleWorker::handleSurfaceInteraction(int depth,
		bool caustic, const Intersection &its, const Medium *medium,
		const Spectrum &weight) {
	const ProjectiveCamera *camera = static_cast<const ProjectiveCamera *>(m_camera.get());
	Point2 screenSample;

	if (camera->positionToSample(its.p, screenSample)) {
		Point cameraPosition = camera->getPosition(screenSample);
	
		Float t = dot(camera->getImagePlaneNormal(), its.p-cameraPosition);
		if (t < camera->getNearClip() || t > camera->getFarClip())
			return;

		if (its.isMediumTransition()) 
			medium = its.getTargetMedium(cameraPosition - its.p);

		Spectrum transmittance = m_scene->getTransmittance(its.p,
				cameraPosition, its.time, medium);

		if (transmittance.isZero())
			return;

		const BSDF *bsdf = its.shape->getBSDF();
		Vector wo = cameraPosition - its.p;
		Float dist = wo.length(); wo /= dist;

		BSDFQueryRecord bRec(its, its.toLocal(wo));
		bRec.quantity = EImportance;

		Float importance; 
		if (m_isPerspectiveCamera)
			importance = ((const PerspectiveCamera *) camera)->importance(screenSample) / (dist * dist);
		else
			importance = 1/camera->areaDensity(screenSample);

		Vector wi = its.toWorld(its.wi);

		/* Prevent light leaks due to the use of shading normals -- [Veach, p. 158] */
		Float wiDotGeoN = dot(its.geoFrame.n, wi),
			  woDotGeoN = dot(its.geoFrame.n, wo);
		if (wiDotGeoN * Frame::cosTheta(bRec.wi) <= 0 || 
			woDotGeoN * Frame::cosTheta(bRec.wo) <= 0)
			return;

		/* Adjoint BSDF for shading normals -- [Veach, p. 155] */
		Float correction = std::abs(
			(Frame::cosTheta(bRec.wi) * woDotGeoN)/
			(Frame::cosTheta(bRec.wo) * wiDotGeoN));

		/* Splat onto the accumulation buffer */
		Ray ray(its.p, wo, 0, dist, its.time);
		Spectrum sampleVal = weight * bsdf->fCos(bRec) 
			* transmittance * (importance * correction);

		m_workResult->splat(screenSample, sampleVal, m_filter);
	}
}