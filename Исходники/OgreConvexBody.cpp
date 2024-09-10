	//-----------------------------------------------------------------------
	void ConvexBody::extend(const Vector3& pt)
	{
		// Erase all polygons facing towards the point. For all edges that
		// are not removed twice (once in AB and once BA direction) build a
		// convex polygon (triangle) with the point.
		Polygon::EdgeMap edgeMap;

		for ( size_t i = 0; i < getPolygonCount(); ++i )
		{
			const Vector3& normal = getNormal( i );
			// direction of the point in regard to the polygon
			// the polygon is planar so we can take an arbitrary vertex
			Vector3 ptDir  = pt - getVertex( i, 0 );
			ptDir.normalise();

			// remove polygon if dot product is greater or equals null.
			if ( normal.dotProduct( ptDir ) >= 0 )
			{
				// store edges (copy them because if the polygon is deleted
				// its vertices are also deleted)
				storeEdgesOfPolygon( i, &edgeMap );

				// remove polygon
				deletePolygon( i );

				// decrement iterator because of deleted polygon
				--i; 
			}
		}

		// point is already a part of the hull (point lies inside)
		if ( edgeMap.empty() )
			return;

		// remove the edges that are twice in the list (once from each side: AB,BA)

		Polygon::EdgeMap::iterator it;
		// iterate from first to the element before the last one
		for (Polygon::EdgeMap::iterator itStart = edgeMap.begin(); 
			itStart != edgeMap.end(); )
		{
			// compare with iterator + 1 to end
			// don't need to skip last entry in itStart since omitted in inner loop
			it = itStart;
			++it;

			bool erased = false;
			// iterate from itStart+1 to the element before the last one
			for ( ; it != edgeMap.end(); ++it )
			{	
				if (itStart->first.positionEquals(it->second) &&
					 itStart->second.positionEquals(it->first))
				{
					edgeMap.erase(it);
					// increment itStart before deletion (iterator invalidation)
					Polygon::EdgeMap::iterator delistart = itStart++;
					edgeMap.erase(delistart);
					erased = true;

					break; // found and erased
				}
			}
			// increment itStart if we didn't do it when erasing
			if (!erased)
				++itStart;

		}

		// use the remaining edges to build triangles with the point
		// the vertices of the edges are in ccw order (edgePtA-edgePtB-point
		// to form a ccw polygon)
		while ( !edgeMap.empty() )
		{
			Polygon::EdgeMap::iterator mapIt = edgeMap.begin();

			// build polygon it.first, it.second, point
			Polygon *p = allocatePolygon();

			p->insertVertex(mapIt->first);
			p->insertVertex(mapIt->second);

			p->insertVertex( pt );
			// attach polygon to body
			insertPolygon( p );

			// erase the vertices from the list
			// pointers are now held by the polygon
			edgeMap.erase( mapIt );
		}
	}