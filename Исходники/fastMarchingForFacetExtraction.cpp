float FastMarchingForFacetExtraction::computeTCoefApprox(CCLib::FastMarching::Cell* originCell, CCLib::FastMarching::Cell* destCell) const
{
	PlanarCell* oCell = static_cast<PlanarCell*>(originCell);
	PlanarCell* dCell = static_cast<PlanarCell*>(destCell);

	//compute the 'confidence' relatively to the neighbor cell
	//1) it depends on the angle between the current cell's orientation
	//	and its neighbor's orientation (symmetric)
	//2) it depends on whether the neighbor's relative position is
	//	compatible with the current cell orientation (symmetric)
	float orientationConfidence = 0;
	{
		CCVector3 AB = dCell->C - oCell->C;
		AB.normalize();

		float psOri = fabs(static_cast<float>(AB.dot(oCell->N))); //ideal: 90 degrees
		float psDest = fabs(static_cast<float>(AB.dot(dCell->N))); //ideal: 90 degrees
		orientationConfidence = (psOri + psDest)/2; //between 0 and 1 (ideal: 0)
	}

	//add reprojection error into balance
	if (m_useRetroProjectionError && m_octree && oCell->N.norm2() != 0)
	{
		PointCoordinateType theLSQPlaneEquation[4];
		theLSQPlaneEquation[0] = oCell->N.x;
		theLSQPlaneEquation[1] = oCell->N.y;
		theLSQPlaneEquation[2] = oCell->N.z;
		theLSQPlaneEquation[3] = oCell->C.dot(oCell->N);

		CCLib::ReferenceCloud Yk(m_octree->associatedCloud());
		if (m_octree->getPointsInCell(oCell->cellCode,m_gridLevel,&Yk,true))
		{
			ScalarType reprojError = CCLib::DistanceComputationTools::ComputeCloud2PlaneDistance(&Yk,theLSQPlaneEquation,m_errorMeasure);
			if (reprojError >= 0)
				return (1.0f-orientationConfidence) * static_cast<float>(reprojError);
		}
	}

	return (1.0f-orientationConfidence) /** oCell->planarError*/;
}