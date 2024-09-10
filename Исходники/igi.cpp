Spectrum IGIIntegrator::Li(const Scene *scene,
		const RayDifferential &ray, const Sample *sample,
		   float *alpha) const {
	Spectrum L(0.);
	Intersection isect;
	if (scene->Intersect(ray, &isect)) {
		if (alpha) *alpha = 1.;
		Vector wo = -ray.d;
		// Compute emitted light if ray hit an area light source
		L += isect.Le(wo);
		// Evaluate BSDF at hit point
		BSDF *bsdf = isect.GetBSDF(ray);
		const Point &p = bsdf->dgShading.p;
		const Normal &n = bsdf->dgShading.nn;
		L += UniformSampleAllLights(scene, p, n,
					    wo, bsdf, sample,
					    lightSampleOffset, bsdfSampleOffset,
					    bsdfComponentOffset);
		// Compute indirect illumination with virtual lights
		u_int lSet = min(u_int(sample->oneD[vlSetOffset][0] * nLightSets),
		                 nLightSets-1);
		for (u_int i = 0; i < virtualLights[lSet].size(); ++i) {
			const VirtualLight &vl = virtualLights[lSet][i];
			// Add contribution from _VirtualLight_ _vl_
			// Ignore light if it's too close to current point
			float d2 = DistanceSquared(p, vl.p);
			//if (d2 < .8 * minDist2) continue;
			float distScale = SmoothStep(.8 * minDist2, 1.2 * minDist2, d2);
			// Compute virtual light's tentative contribution _Llight_
			Vector wi = Normalize(vl.p - p);
			Spectrum f = distScale * bsdf->f(wo, wi);
			if (f.Black()) continue;
			float G = AbsDot(wi, n) * AbsDot(wi, vl.n) / d2;
			Spectrum Llight = indirectScale * f * G * vl.Le /
				virtualLights[lSet].size();
			Llight *= scene->Transmittance(Ray(p, vl.p - p));
			// Possibly skip shadow ray with Russian roulette
			if (Llight.y() < rrThreshold) {
				float continueProbability = .1f;
				if (RandomFloat() > continueProbability)
					continue;
				Llight /= continueProbability;
			}
			static StatsCounter vlsr("IGI Integrator", "Shadow Rays to Virtual Lights"); //NOBOOK
			++vlsr; //NOBOOK
			if (!scene->IntersectP(Ray(p, vl.p - p, RAY_EPSILON,
					1.f - RAY_EPSILON)))
				L += Llight;
		}
		// Trace rays for specular reflection and refraction
		if (specularDepth++ < maxSpecularDepth) {
			Vector wi;
			// Trace rays for specular reflection and refraction
			Spectrum f = bsdf->Sample_f(wo, &wi,
						BxDFType(BSDF_REFLECTION | BSDF_SPECULAR));
			if (!f.Black()) {
				// Compute ray differential _rd_ for specular reflection
				RayDifferential rd(p, wi);
				rd.hasDifferentials = true;
				rd.rx.o = p + isect.dg.dpdx;
				rd.ry.o = p + isect.dg.dpdy;
				// Compute differential reflected directions
				Normal dndx = bsdf->dgShading.dndu * bsdf->dgShading.dudx +
					bsdf->dgShading.dndv * bsdf->dgShading.dvdx;
				Normal dndy = bsdf->dgShading.dndu * bsdf->dgShading.dudy +
					bsdf->dgShading.dndv * bsdf->dgShading.dvdy;
				Vector dwodx = -ray.rx.d - wo, dwody = -ray.ry.d - wo;
				float dDNdx = Dot(dwodx, n) + Dot(wo, dndx);
				float dDNdy = Dot(dwody, n) + Dot(wo, dndy);
				rd.rx.d = wi -
					dwodx + 2 * Vector(Dot(wo, n) * dndx +
						 dDNdx * n);
				rd.ry.d = wi -
					dwody + 2 * Vector(Dot(wo, n) * dndy +
						 dDNdy * n);
				L += scene->Li(rd, sample) * f * AbsDot(wi, n);
			}
			f = bsdf->Sample_f(wo, &wi,
					   BxDFType(BSDF_TRANSMISSION | BSDF_SPECULAR));
			if (!f.Black()) {
				// Compute ray differential _rd_ for specular transmission
				RayDifferential rd(p, wi);
				rd.hasDifferentials = true;
				rd.rx.o = p + isect.dg.dpdx;
				rd.ry.o = p + isect.dg.dpdy;

				float eta = bsdf->eta;
				Vector w = -wo;
				if (Dot(wo, n) < 0) eta = 1.f / eta;

				Normal dndx = bsdf->dgShading.dndu * bsdf->dgShading.dudx + bsdf->dgShading.dndv * bsdf->dgShading.dvdx;
				Normal dndy = bsdf->dgShading.dndu * bsdf->dgShading.dudy + bsdf->dgShading.dndv * bsdf->dgShading.dvdy;

				Vector dwodx = -ray.rx.d - wo, dwody = -ray.ry.d - wo;
				float dDNdx = Dot(dwodx, n) + Dot(wo, dndx);
				float dDNdy = Dot(dwody, n) + Dot(wo, dndy);

				float mu = eta * Dot(w, n) - Dot(wi, n);
				float dmudx = (eta - (eta*eta*Dot(w,n))/Dot(wi, n)) * dDNdx;
				float dmudy = (eta - (eta*eta*Dot(w,n))/Dot(wi, n)) * dDNdy;

				rd.rx.d = wi + eta * dwodx - Vector(mu * dndx + dmudx * n);
				rd.ry.d = wi + eta * dwody - Vector(mu * dndy + dmudy * n);
				L += scene->Li(rd, sample) * f * AbsDot(wi, n);
			}
		}
		--specularDepth;
	}
	else {
		// Handle ray with no intersection
		if (alpha) *alpha = 0.;
		for (u_int i = 0; i < scene->lights.size(); ++i)
			L += scene->lights[i]->Le(ray);
		if (alpha && !L.Black()) *alpha = 1.;
		return L;
	}
	return L;
}