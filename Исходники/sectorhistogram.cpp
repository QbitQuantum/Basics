void SectorHistogram::construct( const Billon &billon, const Interval<uint> &sliceInterval, const Interval<int> &intensity,
								 const uint &zMotionMin, const int &radiusAroundPith )
{
	clear();

	if ( billon.hasPith() && sliceInterval.isValid() && sliceInterval.width() > 0 )
	{
		const int &width = billon.n_cols;
		const int &height = billon.n_rows;
		const qreal squareRadius = qPow(radiusAroundPith,2);

		fill(0.,PieChartSingleton::getInstance()->nbSectors());

		QVector<int> circleLines;
		circleLines.reserve(2*radiusAroundPith+1);
		for ( int lineIndex=-radiusAroundPith ; lineIndex<=radiusAroundPith ; ++lineIndex )
		{
			circleLines.append(qSqrt(squareRadius-qPow(lineIndex,2)));
		}

		QVector<int>::ConstIterator circlesLinesIterator;
		int iRadius;
		uint diff;
		iCoord2D currentPos;

		// Calcul du diagramme en parcourant les tranches du billon comprises dans l'intervalle
		for ( uint k=sliceInterval.min() ; k<=sliceInterval.max() ; ++k )
		{
			const Slice &currentSlice = billon.slice(k);
			const Slice &previousSlice = billon.previousSlice(k);
			const iCoord2D &currentPithCoord = billon.pithCoord(k);
			currentPos.y = currentPithCoord.y-radiusAroundPith;
			for ( circlesLinesIterator = circleLines.constBegin() ; circlesLinesIterator != circleLines.constEnd() ; ++circlesLinesIterator )
			{
				iRadius = *circlesLinesIterator;
				currentPos.x = currentPithCoord.x-iRadius;
				iRadius += currentPithCoord.x;
				while ( currentPos.x <= iRadius )
				{
					if ( currentPos.x < width && currentPos.y < height && intensity.containsOpen(currentSlice.at(currentPos.y,currentPos.x)) &&
						 intensity.containsOpen(previousSlice.at(currentPos.y,currentPos.x)) )
					{
						diff = billon.zMotion(currentPos.x,currentPos.y,k);
						//if ( motionInterval.containsClosed(diff) )
						if ( diff >= zMotionMin )
						{
							(*this)[PieChartSingleton::getInstance()->sectorIndexOfAngle( currentPithCoord.angle(currentPos) )] += diff-zMotionMin;
						}
					}
					currentPos.x++;
				}
				currentPos.y++;
			}
		}
	}
}