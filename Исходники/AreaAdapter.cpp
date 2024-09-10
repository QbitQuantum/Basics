WFMath::Polygon<2> AreaAdapter::getDefaultPolygon() const
{
	WFMath::Polygon<2> poly;
	poly.addCorner(0, WFMath::Point<2>(-1, -1));
	poly.addCorner(1, WFMath::Point<2>(-1, 1));
	poly.addCorner(2, WFMath::Point<2>(1, 1));
	poly.addCorner(3, WFMath::Point<2>(1, -1));
	return poly;
}