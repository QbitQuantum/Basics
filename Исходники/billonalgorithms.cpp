	QVector<rCoord2D> restrictedAreaVertex( const Billon &billon, const Interval<uint> & sliceInterval, const uint & nbPolygonVertex, const int & intensityThreshold )
	{
		Q_ASSERT_X( nbPolygonVertex>0 , "BillonTpl<T>::getRestrictedAreaVertex", "nbPolygonVertex arguments equals to 0 => division by zero" );

		QVector<rCoord2D> vectAllVertex;
		if ( billon.hasPith() )
		{
			const int width = billon.n_cols;
			const int height = billon.n_rows;
			const qreal angleIncrement = TWO_PI/static_cast<qreal>(nbPolygonVertex);
			rCoord2D edge, center;
			rVec2D direction;
			qreal orientation;
			for ( uint indexSlice = sliceInterval.min() ; indexSlice<=sliceInterval.max() ; ++indexSlice )
			{
				const Slice & currentSlice = billon.slice(indexSlice);
				center.x = billon.pithCoord(indexSlice).x;
				center.y = billon.pithCoord(indexSlice).y;
				orientation = 0.;
				while (orientation < TWO_PI)
				{
					orientation += angleIncrement;
					direction = rVec2D(qCos(orientation),qSin(orientation));
					edge = center + direction*30;
					while ( edge.x>0. && edge.y>0. && edge.x<width && edge.y<height && currentSlice(edge.y,edge.x) >= intensityThreshold )
					{
						edge += direction;
					}
					vectAllVertex.push_back(edge);
				}
			}
		}
		return vectAllVertex;
	}