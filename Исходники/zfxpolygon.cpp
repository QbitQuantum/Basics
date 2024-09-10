// split this poly with the given plane, returns two new polys
// on front and back side of the plane.
void ZFXPolygon::Clip(const ZFXPlane &Plane, ZFXPolygon *pFront,
	ZFXPolygon *pBack) {
	if (!pFront && !pBack) return;

	ZFXVector vcHit, vcA, vcB;
	ZFXRay    Ray;

	// cast away const
	ZFXPlane  *pPlane = ((ZFXPlane*)&Plane);

	unsigned int nNumFront = 0,     // number points on frontside
		nNumBack = 0,      // number points on backside
		nLoop = 0,
		nCurrent = 0;

	ZFXVector *pvcFront = new ZFXVector[m_NumP * 3];
	ZFXVector *pvcBack = new ZFXVector[m_NumP * 3];

	// classify the first vertex and fill to appropriate list
	switch (pPlane->Classify(m_pPoints[0])) {
	case ZFXFRONT:
		pvcFront[nNumFront++] = m_pPoints[0];
		break;
	case ZFXBACK:
		pvcBack[nNumBack++] = m_pPoints[0];
		break;
	case ZFXPLANAR:
		pvcBack[nNumBack++] = m_pPoints[0];
		pvcFront[nNumFront++] = m_pPoints[0];
		break;
	default: return;
	}

	// loop through all points of the polygon
	for (nLoop = 1; nLoop < (m_NumP + 1); nLoop++) {

		if (nLoop == m_NumP) nCurrent = 0;
		else nCurrent = nLoop;

		// take two neighboring points from the poly
		vcA = m_pPoints[nLoop - 1];
		vcB = m_pPoints[nCurrent];

		// classify points with respect to the plane
		int nClass = pPlane->Classify(vcB);
		int nClassA = pPlane->Classify(vcA);

		// if planar then put him to both sides
		if (nClass == ZFXPLANAR) {
			pvcBack[nNumBack++] = m_pPoints[nCurrent];
			pvcFront[nNumFront++] = m_pPoints[nCurrent];
		}
		// else check if this edge intersects the plane
		else {
			Ray.m_vcOrig = vcA;
			Ray.m_vcDir = vcB - vcA;

			float fLength = Ray.m_vcDir.GetLength();

			if (fLength != 0.0f) Ray.m_vcDir /= fLength;

			if (Ray.Intersects(Plane, false, fLength, 0, &vcHit)
				&& (nClassA != ZFXPLANAR)) {

				// put the intersection point as new point for both
				pvcBack[nNumBack++] = vcHit;
				pvcFront[nNumFront++] = vcHit;

				// then sort the current point
				if (nClass == ZFXFRONT) {
					if (nCurrent != 0)
						pvcFront[nNumFront++] = m_pPoints[nCurrent];
				} // if [FRONT]
				else if (nClass == ZFXBACK) {
					if (nCurrent != 0)
						pvcBack[nNumBack++] = m_pPoints[nCurrent];
				} // else [BACK]		
			}
			// if no intersection then just sort this point
			else {
				if (nCurrent == 0) continue;

				if (nClass == ZFXFRONT) {
					pvcFront[nNumFront++] = m_pPoints[nCurrent];
				}
				else if (nClass == ZFXBACK) {
					pvcBack[nNumBack++] = m_pPoints[nCurrent];
				}
				else {
					return; // should not happen
				}
			}
		}
	} // for [NumP]


	/* now we have the vertices for both new polys ready.
	   lets take care of the index lists now              */

	unsigned int I0, I1, I2;

	unsigned int *pnFront = NULL;
	unsigned int *pnBack = NULL;

	if (nNumFront > 2) {
		pnFront = new unsigned int[(nNumFront - 2) * 3];

		for (nLoop = 0; nLoop < (nNumFront - 2); nLoop++) {
			if (nLoop == 0) { I0 = 0; I1 = 1; I2 = 2; }
			else { I1 = I2; I2++; }

			pnFront[(nLoop * 3)] = I0;
			pnFront[(nLoop * 3) + 1] = I1;
			pnFront[(nLoop * 3) + 2] = I2;
		}
	}

	if (nNumBack > 2) {
		pnBack = new unsigned int[(nNumBack - 2) * 3];

		for (nLoop = 0; nLoop < (nNumBack - 2); nLoop++) {
			if (nLoop == 0) { I0 = 0; I1 = 1; I2 = 2; }
			else { I1 = I2; I2++; }

			pnBack[(nLoop * 3)] = I0;
			pnBack[(nLoop * 3) + 1] = I1;
			pnBack[(nLoop * 3) + 2] = I2;
		}
	}

	// now fuel in the information to the new poly objects
	if (pFront && pnFront) {
		pFront->Set(pvcFront, nNumFront, pnFront, (nNumFront - 2) * 3);

		// make sure new one has same orientation as original
		if (pFront->GetPlane().m_vcN * m_Plane.m_vcN < 0.0f)
			pFront->SwapFaces();
	}

	if (pBack && pnBack) {
		pBack->Set(pvcBack, nNumBack, pnBack, (nNumBack - 2) * 3);

		// make sure new one has same orientation as original
		if (pBack->GetPlane().m_vcN * m_Plane.m_vcN < 0.0f)
			pBack->SwapFaces();
	}

	// free temporary memory
	if (pvcFront) { delete[] pvcFront; }
	if (pvcBack)  { delete[] pvcBack; }
	if (pnFront)  { delete[] pnFront; }
	if (pnBack)   { delete[] pnBack; }
} // Clip