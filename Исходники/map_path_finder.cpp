int MapPathFinder::CalculatePath(const Map_BoolType &MainMap, const POSE &Start, const POSE &Destination, MapPath &Path)
{
	// Check that start is a valid position
	if( MainMap.GetPixel(Start.Position) != OCCUPANCYGRID_DISCRETE_EMPTY )
		return -1;

	// Get Distance Map
	Map_IntType distMap;
	MapPathFinder::CalculateDistMap(MainMap, Destination.Position, distMap);

	// Check if Destination is reachable from start
	unsigned int curDist, nextDist;
	if(distMap.GetPixel(Start.Position, curDist) < 0)
		return -2;
	if(curDist >= distMap.GetHeight()*distMap.GetWidth())
		return -3;


	// Follow negative gradient from start until destination is reached
	PATH_DATA_LOCAL newMoveOrder;
	POSE curPose = Start;
	POSE nextPose;

	newMoveOrder.PathLength		= 0;
	newMoveOrder.RotAngle		= 0;

	while(curDist > 0)
	{
		// Look at neighbors and find lowest distance to target
		nextDist = curDist;
		for(int i=-1; i<=1; i++)
		{
			for(int j=-1; j<=1; j++)
			{
				unsigned int	tmpDist;
				POS_2D			tmpPos;

				tmpPos.X = curPose.Position.X + i;
				tmpPos.Y = curPose.Position.Y + j;

				// Check that this pixel is valid
				if(distMap.GetPixel(tmpPos, tmpDist) < 0)
					continue;

				// Check if new distance is less than old distance and if so, set as next position
				if(tmpDist < nextDist)
				{
					nextDist = tmpDist;
					nextPose.Position = tmpPos;
				}
			}
		}

		// After going through neighbors, check that a lower distance was found
		//	Report error if not
		if(nextDist <= curDist)
		{
			std::cerr << "MapPathFinder::CalculatePath() ERROR: No lower distance found\n";
			return -4;
		}

		// Check whether old move order simply needs to be elongated, or if a new move order is required
		nextPose.RotationAngle = atan2((nextPose.Position.Y - curPose.Position.Y), (nextPose.Position.X - curPose.Position.X));
		if(CompareAngles(nextPose.RotationAngle, curPose.RotationAngle))
		{
			// Both angles are equal, just elongate current move order
			newMoveOrder.PathLength += sqrt((nextPose.Position.Y - curPose.Position.Y)*(nextPose.Position.Y - curPose.Position.Y) + (nextPose.Position.X-curPose.Position.X)*(nextPose.Position.X-curPose.Position.X));
		}
		else
		{
			// Add old order to Path
			Path.AddMoveOrder(newMoveOrder);

			// Create new order
			newMoveOrder.RotAngle		= nextPose.RotationAngle-curPose.RotationAngle;			// Rotate to new movement direction
			newMoveOrder.PathLength		= sqrt((nextPose.Position.Y - curPose.Position.Y)*(nextPose.Position.Y - curPose.Position.Y) + (nextPose.Position.X-curPose.Position.X)*(nextPose.Position.X-curPose.Position.X));
		}

		// Update for next round
		curPose = nextPose;
		curDist = nextDist;
	}

	// Check whether last move order needs to be added to Path
	if(newMoveOrder.PathLength != 0)
	{
		Path.AddMoveOrder(newMoveOrder);
	}

	// Check whether the robot needs to be rotated to face the correct direction
	if(curPose.RotationAngle != Destination.RotationAngle)
	{
		newMoveOrder.PathLength = 0;
		newMoveOrder.RotAngle   = Destination.RotationAngle - curPose.RotationAngle;

		Path.AddMoveOrder(newMoveOrder);
	}

	return 1;
}