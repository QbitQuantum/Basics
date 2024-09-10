//ctx add
BWAPI::TilePosition BuildingPlacer::getBuildLocationFarFromChokePoint(const Building & b, int buildDist, bool horizontalOnly, bool flag) const
{
	SparCraft::Timer t;
	t.start();

	BWAPI::TilePosition startTitlePos = BWAPI::Broodwar->self()->getStartLocation();
	BWTA::Chokepoint *chokePoint = BWTA::getNearestChokepoint(startTitlePos);
	BWAPI::Position chokeCenterPosition = chokePoint->getCenter();
	BWTA::Region *baseRegion = BWTA::getRegion(BWAPI::Broodwar->self()->getStartLocation());
	BWTA::Polygon basePolygon = baseRegion->getPolygon();
	BWAPI::Position farPosition =  BWAPI::Position(0, 0);
	BWAPI::TilePosition resultPosition = BWAPI::TilePosition(0, 0);
	double dis = 0.0;

	

	for (int i = 0; i < (int)basePolygon.size(); i++) {
		BWAPI::Position point = basePolygon[i];
		double ms1 = t.getElapsedTimeInMilliSec();
		if (point.getDistance(chokeCenterPosition) > dis) {
			dis = point.getDistance(chokeCenterPosition);
			farPosition = point;
		}
	}

	const std::vector<BWAPI::TilePosition> & closestToBuilding = MapTools::Instance().getClosestTilesTo(BWAPI::Position(b.desiredPosition));

	//get best solution
	dis = farPosition.getDistance(BWAPI::Position(startTitlePos));
	
	if (flag == true) {
		for (size_t i = 0; i < closestToBuilding.size(); ++i)
		{
			double ms1 = t.getElapsedTimeInMilliSec();
			if (canBuildHereWithSpace(closestToBuilding[i], b, buildDist, horizontalOnly) && dis > farPosition.getDistance(BWAPI::Position(closestToBuilding[i])))
			{
				resultPosition = closestToBuilding[i];
				break;
				//return closestToBuilding[i];
			}
		}
	}
	else {
		for (size_t i = 0; i < closestToBuilding.size(); ++i)
		{
			double ms1 = t.getElapsedTimeInMilliSec();
			if (canBuildHereWithSpace(closestToBuilding[i], b, buildDist, horizontalOnly) && dis < farPosition.getDistance(BWAPI::Position(closestToBuilding[i])))
			{
				resultPosition = closestToBuilding[i];
				break;
				//return closestToBuilding[i];
			}
		}
	}
	
	if (!basePolygon.isInside(BWAPI::Position(resultPosition))) {
		resultPosition = getBuildLocationNear(b, buildDist, horizontalOnly);
	}

	return resultPosition;
}