std::pair< Point<float>, float > Stippler::calculateCellCentroid( Point<float> &inside, EdgeList &edgeList ) {
	using std::make_pair;
	using std::numeric_limits;
	using std::vector;
	using std::floor;
	using std::ceil;
	using std::abs;
	using std::sqrt;
	using std::pow;

	vector< Line<float> > clipLines;
	Extents<float> extent = getCellExtents(edgeList);

	unsigned int x, y;

	float xDiff = ( extent.maxX - extent.minX );
	float yDiff = ( extent.maxY - extent.minY );

	unsigned int tileWidth = (unsigned int)ceil(xDiff) * parameters.subpixels;
	unsigned int tileHeight = (unsigned int)ceil(yDiff) * parameters.subpixels;

	float xStep = xDiff / (float)tileWidth;
	float yStep = yDiff / (float)tileHeight;

	float spotDensity, areaDensity = 0.0f, maxAreaDensity = 0.0f;
	float xSum = 0.0f;
	float ySum = 0.0f;

	float xCurrent;
	float yCurrent;

	// compute the clip lines
	for ( EdgeList::iterator value_iter = edgeList.begin(); value_iter != edgeList.end(); ++value_iter ) {
		Line<float> l = createClipLine( inside.x, inside.y, 
			value_iter->begin.x, value_iter->begin.y,
			value_iter->end.x, value_iter->end.y );
	
		if (l.a < numeric_limits<float>::epsilon() && abs(l.b) < numeric_limits<float>::epsilon()) {
			continue;
		}

		clipLines.push_back(l);
	}

	for ( y = 0, yCurrent = extent.minY; y < tileHeight; ++y, yCurrent += yStep ) {
		for ( x = 0, xCurrent = extent.minX; x < tileWidth; ++x, xCurrent += xStep ) {
			// a point is outside of the polygon if it is outside of all clipping planes
			bool outside = false;
			for ( vector< Line<float> >::iterator iter = clipLines.begin(); iter != clipLines.end(); iter++ ) {
				if ( xCurrent * iter->a + yCurrent * iter->b + iter->c >= 0.0f ) {
					outside = true;
					break;
				}
			}

			if (!outside) {
				spotDensity = image.getIntensity(xCurrent, yCurrent);

				areaDensity += spotDensity;
				maxAreaDensity += 255.0f;
				xSum += spotDensity * xCurrent;
				ySum += spotDensity * yCurrent;
			}
		}
	}

	float area = areaDensity * xStep * yStep / 255.0f;
	float maxArea = maxAreaDensity * xStep * yStep / 255.0f;

	Point<float> pt;
	if (areaDensity > numeric_limits<float>::epsilon()) {
		pt.x = xSum / areaDensity;
		pt.y = ySum / areaDensity;
	} else {
		// if for some reason, the cell is completely white, then the centroid does not move
		pt.x = inside.x;
		pt.y = inside.y;
	}

	float closest = numeric_limits<float>::max(),
		  farthest = numeric_limits<float>::min(),
		  distance;
	float x0 = pt.x, y0 = pt.y,
	      x1, x2, y1, y2;

	for ( EdgeList::iterator value_iter = edgeList.begin(); value_iter != edgeList.end(); ++value_iter ) {
		x1 = value_iter->begin.x; x2 = value_iter->end.x;
		y1 = value_iter->begin.y; y2 = value_iter->end.y;

		distance = abs( ( x2 - x1 ) * ( y1 - y0 ) - ( x1 - x0 ) * ( y2 - y1 ) ) / sqrt( pow( x2 - x1, 2.0f ) + pow( y2 - y1, 2.0f ) );
		if ( closest > distance ) {
			closest = distance;
		}
		if ( farthest < distance ) {
			farthest = distance;
		}
	}

	float radius;
	if ( parameters.noOverlap ) {
		radius = closest;
	} else {
		radius = farthest;
	}
	radius *= area / maxArea;

	return make_pair( pt, radius );
}