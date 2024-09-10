	Spectrum Li(const RayDifferential &ray, RadianceQueryRecord &rRec) const {
		Spectrum LiSurf(0.0f), LiMedium(0.0f), transmittance(1.0f);
		Intersection &its = rRec.its;
		const Scene *scene = rRec.scene;

		bool cacheQuery = (rRec.extra & RadianceQueryRecord::ECacheQuery);
		bool adaptiveQuery = (rRec.extra & RadianceQueryRecord::EAdaptiveQuery);

		/* Perform the first ray intersection (or ignore if the
		   intersection has already been provided). */
		rRec.rayIntersect(ray);

		if (rRec.medium) {
			Ray mediumRaySegment(ray, 0, its.t);
			transmittance = rRec.medium->evalTransmittance(mediumRaySegment);
			mediumRaySegment.mint = ray.mint;
			if (rRec.type & RadianceQueryRecord::EVolumeRadiance &&
					(rRec.depth < m_maxDepth || m_maxDepth < 0) && m_bre.get() != NULL)
				LiMedium = m_bre->query(mediumRaySegment, rRec.medium);
		}

		if (!its.isValid()) {
			/* If no intersection could be found, possibly return
			   attenuated radiance from a background luminaire */
			if ((rRec.type & RadianceQueryRecord::EEmittedRadiance) && !m_hideEmitters)
				LiSurf = scene->evalEnvironment(ray);
			return LiSurf * transmittance + LiMedium;
		}

		/* Possibly include emitted radiance if requested */
		if (its.isEmitter() && (rRec.type & RadianceQueryRecord::EEmittedRadiance) && !m_hideEmitters)
			LiSurf += its.Le(-ray.d);

		/* Include radiance from a subsurface scattering model if requested */
		if (its.hasSubsurface() && (rRec.type & RadianceQueryRecord::ESubsurfaceRadiance))
			LiSurf += its.LoSub(scene, rRec.sampler, -ray.d, rRec.depth);

		const BSDF *bsdf = its.getBSDF(ray);

		if (rRec.depth >= m_maxDepth && m_maxDepth > 0)
			return LiSurf * transmittance + LiMedium;

		unsigned int bsdfType = bsdf->getType() & BSDF::EAll;

		/* Irradiance cache query -> treat as diffuse */
		bool isDiffuse = (bsdfType == BSDF::EDiffuseReflection) || cacheQuery;

		bool hasSpecular = bsdfType & BSDF::EDelta;

		/* Exhaustively recurse into all specular lobes? */
		bool exhaustiveSpecular = rRec.depth < m_maxSpecularDepth && !cacheQuery;

		if (isDiffuse && (dot(its.shFrame.n, ray.d) < 0 || (bsdf->getType() & BSDF::EBackSide))) {
			/* 1. Diffuse indirect */
			int maxDepth = m_maxDepth == -1 ? INT_MAX : (m_maxDepth-rRec.depth);
			if (rRec.type & RadianceQueryRecord::EIndirectSurfaceRadiance && m_globalPhotonMap.get())
				LiSurf += m_globalPhotonMap->estimateIrradiance(its.p,
					its.shFrame.n, m_globalLookupRadius, maxDepth,
					m_globalLookupSize) * bsdf->getDiffuseReflectance(its) * INV_PI;
			if (rRec.type & RadianceQueryRecord::ECausticRadiance && m_causticPhotonMap.get())
				LiSurf += m_causticPhotonMap->estimateIrradiance(its.p,
					its.shFrame.n, m_causticLookupRadius, maxDepth,
					m_causticLookupSize) * bsdf->getDiffuseReflectance(its) * INV_PI;
		}

		if (hasSpecular && exhaustiveSpecular
			&& (rRec.type & RadianceQueryRecord::EIndirectSurfaceRadiance)) {
			/* 1. Specular indirect */
			int compCount = bsdf->getComponentCount();
			RadianceQueryRecord rRec2;
			for (int i=0; i<compCount; i++) {
				unsigned int type = bsdf->getType(i);
				if (!(type & BSDF::EDelta))
					continue;
				/* Sample the BSDF and recurse */
				BSDFSamplingRecord bRec(its, rRec.sampler, ERadiance);
				bRec.component = i;
				Spectrum bsdfVal = bsdf->sample(bRec, Point2(0.5f));
				if (bsdfVal.isZero())
					continue;

				rRec2.recursiveQuery(rRec, RadianceQueryRecord::ERadiance);
				RayDifferential bsdfRay(its.p, its.toWorld(bRec.wo), ray.time);
				if (its.isMediumTransition())
					rRec2.medium = its.getTargetMedium(bsdfRay.d);

				LiSurf += bsdfVal * m_parentIntegrator->Li(bsdfRay, rRec2);
			}
		}

		/* Estimate the direct illumination if this is requested */
		int numEmitterSamples = m_directSamples, numBSDFSamples;
		Float weightLum, weightBSDF;
		Point2 *sampleArray;
		Point2 sample;

		if (rRec.depth > 1 || cacheQuery || adaptiveQuery) {
			/* This integrator is used recursively by another integrator.
			   Be less accurate as this sample will not directly be observed. */
			numBSDFSamples = numEmitterSamples = 1;
			weightLum = weightBSDF = 1.0f;
		} else {
			if (isDiffuse) {
				numBSDFSamples = m_directSamples;
				weightBSDF = weightLum = m_invEmitterSamples;
			} else {
				numBSDFSamples = m_glossySamples;
				weightLum = m_invEmitterSamples;
				weightBSDF = m_invGlossySamples;
			}
		}

		if ((bsdfType & BSDF::ESmooth) && (rRec.type & RadianceQueryRecord::EDirectSurfaceRadiance)) {
			DirectSamplingRecord dRec(its);

			if (numEmitterSamples > 1) {
				sampleArray = rRec.sampler->next2DArray(m_directSamples);
			} else {
				sample = rRec.nextSample2D(); sampleArray = &sample;
			}

			for (int i=0; i<numEmitterSamples; ++i) {
				int interactions = m_maxDepth - rRec.depth - 1;
				Spectrum value = scene->sampleAttenuatedEmitterDirect(
						dRec, its, rRec.medium, interactions,
						sampleArray[i], rRec.sampler);

				/* Estimate the direct illumination if this is requested */
				if (!value.isZero()) {
					const Emitter *emitter = static_cast<const Emitter *>(dRec.object);

					/* Allocate a record for querying the BSDF */
					BSDFSamplingRecord bRec(its, its.toLocal(dRec.d));

					/* Evaluate BSDF * cos(theta) */
					const Spectrum bsdfVal = bsdf->eval(bRec);

					if (!bsdfVal.isZero()) {
						/* Calculate prob. of having sampled that direction
						   using BSDF sampling */

						if (!hasSpecular || exhaustiveSpecular)
							bRec.typeMask = BSDF::ESmooth;

						Float bsdfPdf = (emitter->isOnSurface()
								&& dRec.measure == ESolidAngle
								&& interactions == 0)
								? bsdf->pdf(bRec) : (Float) 0.0f;

						/* Weight using the power heuristic */
						const Float weight = miWeight(dRec.pdf * numEmitterSamples,
								bsdfPdf * numBSDFSamples) * weightLum;

						LiSurf += value * bsdfVal * weight;
					}
				}
			}
		}

		/* ==================================================================== */
		/*                            BSDF sampling                             */
		/* ==================================================================== */

		/* Sample direct compontent via BSDF sampling if this is generally requested AND
		     the BSDF is smooth, or there is a delta component that was not handled by the
			 exhaustive sampling loop above */
		bool bsdfSampleDirect = (rRec.type & RadianceQueryRecord::EDirectSurfaceRadiance) &&
			((bsdfType & BSDF::ESmooth) || (hasSpecular && !exhaustiveSpecular));

		/* Sample indirect component via BSDF sampling if this is generally requested AND
		    the BSDF is non-diffuse (diffuse is handled by the global photon map)
			or there is a delta component that was not handled by the exhaustive sampling loop
			above. */
		bool bsdfSampleIndirect = (rRec.type & RadianceQueryRecord::EIndirectSurfaceRadiance) &&
			!isDiffuse && ((bsdfType & BSDF::ESmooth) || (hasSpecular && !exhaustiveSpecular));

		if (bsdfSampleDirect || bsdfSampleIndirect) {
			if (numBSDFSamples > 1) {
				sampleArray = rRec.sampler->next2DArray(
					std::max(m_directSamples, m_glossySamples));
			} else {
				sample = rRec.nextSample2D(); sampleArray = &sample;
			}

			RadianceQueryRecord rRec2;
			Intersection &bsdfIts = rRec2.its;

			DirectSamplingRecord dRec(its);
			for (int i=0; i<numBSDFSamples; ++i) {
				/* Sample BSDF * cos(theta) */
				BSDFSamplingRecord bRec(its, rRec.sampler, ERadiance);
				if (!hasSpecular || exhaustiveSpecular)
					bRec.typeMask = BSDF::ESmooth;

				Float bsdfPdf;
				Spectrum bsdfVal = bsdf->sample(bRec, bsdfPdf, sampleArray[i]);
				if (bsdfVal.isZero())
					continue;

				/* Trace a ray in this direction */
				RayDifferential bsdfRay(its.p, its.toWorld(bRec.wo), ray.time);

				Spectrum value;
				bool hitEmitter = false;
				if (scene->rayIntersect(bsdfRay, bsdfIts)) {
					/* Intersected something - check if it was a luminaire */
					if (bsdfIts.isEmitter() && bsdfSampleDirect) {
						value = bsdfIts.Le(-bsdfRay.d);
						dRec.setQuery(bsdfRay, bsdfIts);
						hitEmitter = true;
					}
				} else if (bsdfSampleDirect) {
					/* Intersected nothing -- perhaps there is an environment map? */
					const Emitter *env = scene->getEnvironmentEmitter();

					if (env) {
						value = env->evalEnvironment(bsdfRay);
						if (env->fillDirectSamplingRecord(dRec, bsdfRay))
							hitEmitter = true;
					}
				}

				if (hitEmitter) {
					const Float emitterPdf = scene->pdfEmitterDirect(dRec);

					Spectrum transmittance = rRec2.medium ?
						rRec2.medium->evalTransmittance(Ray(bsdfRay, 0, bsdfIts.t)) : Spectrum(1.0f);

					const Float weight = miWeight(bsdfPdf * numBSDFSamples,
						emitterPdf * numEmitterSamples) * weightBSDF;

					LiSurf += value * bsdfVal * weight * transmittance;
				}

				/* Recurse */
				if (bsdfSampleIndirect) {
					rRec2.recursiveQuery(rRec,
						RadianceQueryRecord::ERadianceNoEmission);
					rRec2.type ^= RadianceQueryRecord::EIntersection;

					if (its.isMediumTransition())
						rRec2.medium = its.getTargetMedium(bsdfRay.d);

					LiSurf += bsdfVal * m_parentIntegrator->Li(bsdfRay, rRec2) * weightBSDF;
				}
			}
		}

		return LiSurf * transmittance + LiMedium;
	}