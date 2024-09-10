QPoint OSMARenderMapSource::displayFromCooordinate(const QPointF &coordinate, int zoom)
{
	int tiles_size = (1 << zoom) * tileSize();

	qreal lat_r = atanh(sin(deg2rad(coordinate.y())));
	qreal lon_r = deg2rad(coordinate.x());

	int x =  lon_r * tiles_size / (2 * M_PI) + tiles_size / 2;
	int y = -lat_r * tiles_size / (2 * M_PI) + tiles_size  / 2;

	return QPoint(x, y);
}