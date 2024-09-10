void OffsetWorker::run()
{
	std::auto_ptr<  SFCGAL::Geometry > g( SFCGAL::io::readWkt(wkt_poly));
	OGRFree(wkt_poly); //Not needed after here
	switch ( g->geometryTypeId() ) {
	case SFCGAL::TYPE_POLYGON:
		break;
	default:
		return;
	}
	SFCGAL::Polygon poly = g->as<SFCGAL::Polygon>();
	Polygon_2 p = poly.toPolygon_2(true);

	this->offsetPolygon(p, offset);
}