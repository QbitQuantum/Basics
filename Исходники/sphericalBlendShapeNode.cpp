MStatus sphericalBlendShape::deform(MDataBlock& data, MItGeometry& itGeo, const MMatrix& mat, unsigned int geomIndex) 
{
	MStatus status = MS::kSuccess;

	float env = data.inputValue(envelope).asFloat();
	if (env <= 0.0f) {
		return MS::kSuccess;
	}

	MMatrix spaceMatrix = data.inputValue(aSpaceMatrix).asMatrix();
	short poleAxis		= data.inputValue(aPoleAxis).asShort();
	short seamAxis		= data.inputValue(aSeamAxis).asShort();
	short method		= data.inputValue(aMethod).asShort();
	MMatrix warpMatrix	= data.inputValue(aWarpMatrix).asMatrix();

	MTransformationMatrix warpTransMatrix(warpMatrix);
	MPoint warpPoint = warpTransMatrix.getTranslation(MSpace::kWorld);
	
	status = checkPoleAndSeam(poleAxis, seamAxis);
	CHECK_MSTATUS_AND_RETURN_IT(status);


	MMatrix invGeoMatrix   = mat.inverse();
	MMatrix invSpaceMatrix = spaceMatrix.inverse();

	MPointArray defPoints;
	MPoint* defPoint;
	MPoint inPoint, returnPoint;

	itGeo.allPositions(defPoints);
	unsigned int count = defPoints.length();

	unsigned int i;
	switch(method) {
		// XYZ to Spherical
	case 0:
		for (i=0; i<count; i++) {
			defPoint = &defPoints[i];
			inPoint = *defPoint;

			// bring the point into world space
			inPoint *= invGeoMatrix;
			// bring into local space of the input matrix
			inPoint *= invSpaceMatrix;

			cartesianToSpherical(inPoint, poleAxis, seamAxis, warpPoint, returnPoint);

			// bring the point back into world space
			returnPoint *= spaceMatrix;
			// bring the point back into local space
			returnPoint *= mat;
				
			lerp(*defPoint, returnPoint, env, *defPoint);
		}
		break;

	case 1:
		for (i=0; i<count; i++) {
			defPoint = &defPoints[i];
			inPoint = *defPoint;

			// bring the point into world space
			inPoint *= invGeoMatrix;
			// bring into local space of the input matrix
			inPoint *= invSpaceMatrix;

			sphericalToCartesian(inPoint, poleAxis, seamAxis, warpPoint, returnPoint);

			// bring the point back into world space
			returnPoint *= spaceMatrix;
			// bring the point back into local space
			returnPoint *= mat;
				
			lerp(*defPoint, returnPoint, env, *defPoint);
		}
		break;
	}

	itGeo.setAllPositions(defPoints);

	return MS::kSuccess;
}