const Vector3 RectangleLight::sampleLight(const unsigned int threadID, const Vector3 &from, const Vector3 &normal, const float time, const Scene &scene, const Vector3 &rVec, float &outSpec, bool isSecondary) const
{
	Ray sampleRay(threadID);
	HitInfo sampleHit;
	Vector3 randDir = 0, tmpResult = 0;
	float e1, e2, tmpSpec = 0;
	bool cutOff = false;
	int samplesDone = 0;
	float samplesDoneRecip = 1.0f;
	ALIGN_SSE float falloff = 1.0f;

	do
	{
		// Get a random vector into the light
		e1 = Scene::getRand(threadID);
		e2 = Scene::getRand(threadID);
		e2 = (e2 > 0.99) ? 0.99 : e2;
		randDir = ((m_v1 + e1*(m_v2-m_v1) + e2*(m_v3-m_v1)) - from);

		float nDotL = dot(normal, randDir);
		Vector3 E   = 0;
		float attenuate = 1.0f;

		if (nDotL > epsilon)															// Only do work if light can be hit
		{
			// the inverse-squared falloff
			falloff = randDir.length2();
			ALIGN_SSE float distanceRecip, distance;
#ifndef NO_SSE
			fastrsqrtss(setSSE(falloff), distanceRecip);
			recipss(setSSE(falloff), falloff);
			recipss(setSSE(distanceRecip), distance);
#else
			distance      = sqrtf(falloff);
			distanceRecip = 1.0f / distance;
			falloff       = 1.0f / falloff;
#endif
			randDir *= distanceRecip;
			nDotL   *= distanceRecip;

			if (m_castShadows)
			{
				sampleHit.t = distance - epsilon;									// We need this to account for the fact that we CAN hit geometry, to avoid false positives.
				if (m_fastShadows)
				{
					sampleRay.set(threadID, from, randDir, time, 1.001f, 0, 0, IS_SHADOW_RAY);		// Create shadow ray
					if (scene.trace(threadID, sampleHit, sampleRay, epsilon))					// Quick method, returns any hit
					{
						attenuate = 0.0f;
					}
				}
				else																// Full method, accounts for transparency effects
				{
					float distanceTraversed = 0.0f;
					sampleRay.set(threadID, from, randDir, time, 1.001f, 0, 0, IS_PRIMARY_RAY);		// Create primary ray
					while (distanceTraversed < distance && attenuate > epsilon)
					{
						if (scene.trace(threadID, sampleHit, sampleRay, epsilon))				
						{
							Vector3 hitN; sampleHit.getInterpolatedNormal(hitN);
							float nDL = dot(hitN, -randDir);
							if (nDL > 0.0)											// Only attenuate on incoming direction
							{
								attenuate *= sampleHit.obj->m_material->refractAmt();
							}
							Vector3 newP = Vector3(sampleRay.o[0], sampleRay.o[1], sampleRay.o[2]) + sampleHit.t * randDir;
							sampleRay.set(threadID, newP, randDir, time, 1.001f, 0, 0, IS_PRIMARY_RAY);
							distanceTraversed += sampleHit.t;
						}
						else
						{
							distanceTraversed = distance;
						}
					}
				}
			}
		}
		else
		{
			attenuate = 0.0f;														
		}

		E = m_power * falloff * _1_4PI;										// Light irradiance for this sample
		samplesDone++;
		samplesDoneRecip = 1.0f / (float)samplesDone;

		cutOff = (E * samplesDoneRecip).average() < m_noiseThreshold;		// Stop sampling if contribution is below the noise threshold

		tmpResult += E * attenuate;
		tmpSpec   += max(0.f, dot(rVec, randDir)) * attenuate;

	}  while (samplesDone < m_numSamples && !cutOff);

	outSpec = tmpSpec * samplesDoneRecip;
	return tmpResult * samplesDoneRecip;
}