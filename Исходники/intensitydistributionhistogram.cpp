void IntensityDistributionHistogram::construct( const Billon &billon, const Interval<uint> &sliceInterval, const Interval<uint> &sectorInterval,
												const iCoord2D &pithCoord, const uint &maxDistance, const Interval<int> &intensityInterval,
												const uint &smoothingRadius )
{
	const uint &width = billon.n_cols;
	const uint &height = billon.n_rows;
	const int &minVal = intensityInterval.min();

	uint i, j, k;

	clear();
	resize(intensityInterval.size()+1);

	for ( j=0 ; j<height ; ++j )
	{
		for ( i=0 ; i<width ; ++i )
		{
			if ( sectorInterval.containsClosed(PieChartSingleton::getInstance()->sectorIndexOfAngle(pithCoord.angle(iCoord2D(i,j)))) && pithCoord.euclideanDistance(iCoord2D(i,j)) < maxDistance )
			{
				for ( k=sliceInterval.min() ; k<=sliceInterval.max() ; ++k )
				{
					if ( intensityInterval.containsClosed(billon.slice(k).at(j,i)) ) ++((*this)[billon.slice(k).at(j,i)-minVal]);
				}
			}
		}
	}

	meansSmoothing(smoothingRadius,false);
}