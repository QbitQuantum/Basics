bool TerrainArea::placeArea(WFMath::Polygon<2>& poly)
{
	//If the position if invalid we can't do anything with the area yet.
	if (!mEntity.getPosition().isValid()) {
		return false;
	}

	// transform polygon into terrain coords

	if (mEntity.getOrientation().isValid()) {
		WFMath::Vector<3> xVec = WFMath::Vector<3>(1.0, 0.0, 0.0).rotate(mEntity.getOrientation());
		double theta = atan2(xVec.y(), xVec.x()); // rotation about Z

		WFMath::RotMatrix<2> rm;
		poly.rotatePoint(rm.rotation(theta), WFMath::Point<2>(0, 0));
	}
	poly.shift(WFMath::Vector<2>(mEntity.getPosition().x(), mEntity.getPosition().y()));


	return true;
}