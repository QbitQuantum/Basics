int WorldModel::sonarReading(QPoint const &position, qreal direction) const
{
	int const maxSonarRangeCms = 255;

	QPainterPath const wallPath = buildWallPath();

	for (int currentRangeInCm = 1; currentRangeInCm <= maxSonarRangeCms; ++currentRangeInCm) {
		QPainterPath rayPath = sonarScanningRegion(position, direction, currentRangeInCm);
		if (rayPath.intersects(wallPath)) {
			Tracer::debug(tracer::d2Model, "WorldModel::sonarReading", "Sonar sensor. Reading: " + QString(currentRangeInCm));
			return currentRangeInCm;
		}
	}

	Tracer::debug(tracer::d2Model, "WorldModel::sonarReading", "Sonar sensor. Reading: max (" + QString(maxSonarRangeCms) + ")");
	return maxSonarRangeCms;
}