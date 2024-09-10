float ccFastMarchingForNormsDirection::computePropagationConfidence(DirectionCell* originCell, DirectionCell* destCell) const
{
	//1) it depends on the angle between the current cell's orientation
	//	and its neighbor's orientation (symmetric)
	//2) it depends on whether the neighbor's relative position is
	//	compatible with the current cell orientation (symmetric)
	CCVector3 AB = destCell->C - originCell->C;
	AB.normalize();

	float psOri = fabs(static_cast<float>(AB.dot(originCell->N))); //ideal: 90 degrees
	float psDest = fabs(static_cast<float>(AB.dot(destCell->N))); //ideal: 90 degrees
	float oriConfidence = (psOri + psDest)/2; //between 0 and 1 (ideal: 0)
	
	return 1.0f - oriConfidence;
}