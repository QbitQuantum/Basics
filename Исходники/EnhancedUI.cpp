/* for a given BWTA region, finds corner tile positions for max width and height */
void EnhancedUI::getRegionBoundingTilePositions(const BWTA::Region * region, BWAPI::TilePosition & topLeftTP, 
												BWAPI::TilePosition & topRightTP, BWAPI::TilePosition & bottomRightTP, 
												BWAPI::TilePosition & bottomLeftTP)
{

	BWTA::Polygon poly;
	BWAPI::Position pLeft, pRight, pTop, pBottom;
	/* tile sizes */
	int tsLeft, tsTop, tsRight, tsBottom;
	poly = region->getPolygon();

	pLeft = pRight = pTop = pBottom = (Position) poly[0];

	/* get bounds for BWTA region, map top left is (0,0) */
	for(int j = 1; j < (int)poly.size(); j++)
	{
		if(poly[j].x() < pLeft.x()){
			pLeft = poly[j];
		}
		if(poly[j].x() > pRight.x()){
			pRight = poly[j];
		}
		if(poly[j].y() < pTop.y()){
			pTop = poly[j];
		}
		if(poly[j].y() > pBottom.y()){
			pBottom = poly[j];
		}
	}
	/* align to tile sizes */
	tsLeft = this->getMaxTileSize(pLeft.x());
	tsTop = this->getMaxTileSize(pTop.y());

	tsRight = this->getMinTileSize(pRight.x());
	tsBottom = this->getMinTileSize(pBottom.y());

	/* set tile positions */
	topLeftTP.x() = tsLeft;
	topLeftTP.y() = tsTop;

	topRightTP.x() = tsRight;
	topRightTP.y() = tsTop;

	bottomRightTP.x() = tsRight;
	bottomRightTP.y() = tsBottom;

	bottomLeftTP.x() = tsLeft;
	bottomLeftTP.y() = tsBottom;

}