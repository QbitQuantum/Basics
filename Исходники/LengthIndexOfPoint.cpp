double LengthIndexOfPoint::indexOfFromStart(const Coordinate& inputPt, double minIndex) const
{
	double minDistance = numeric_limits<double>::max();

	double ptMeasure = minIndex;
	double segmentStartMeasure = 0.0;
	LineSegment seg;
	LinearIterator it(linearGeom);
	while (it.hasNext())
	{
		if (! it.isEndOfLine())
		{
			seg.p0 = it.getSegmentStart();
			seg.p1 = it.getSegmentEnd();
			double segDistance = seg.distance(inputPt);
			double segMeasureToPt = segmentNearestMeasure(&seg, inputPt, segmentStartMeasure);
			if (segDistance < minDistance
					&& segMeasureToPt > minIndex)
			{
				ptMeasure = segMeasureToPt;
				minDistance = segDistance;
			}
			segmentStartMeasure += seg.getLength();
		}
		it.next();
	}
	return ptMeasure;
}