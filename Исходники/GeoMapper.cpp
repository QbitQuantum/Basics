void GeoMapper::advancedMapOnMesh(const MeshLib::Mesh* mesh, const std::string &new_geo_name)
{
	const std::vector<GeoLib::Point*> *points (this->_geo_objects.getPointVec(this->_geo_name));
	const std::vector<GeoLib::Polyline*> *org_lines (this->_geo_objects.getPolylineVec(this->_geo_name));

	const GeoLib::AABB<GeoLib::Point> aabb(points->begin(), points->end());
	const double eps = sqrt(std::numeric_limits<float>::epsilon()) *
		               sqrt( MathLib::sqrDist(aabb.getMinPoint(),aabb.getMaxPoint())) ;

	// copy geometry (and set z=0 for all points)
	unsigned nGeoPoints ( points->size() );
	std::vector<GeoLib::Point*> *new_points = new std::vector<GeoLib::Point*>(nGeoPoints);
	for (size_t i=0; i<nGeoPoints; ++i)
		(*new_points)[i] = new GeoLib::Point((*(*points)[i])[0],(*(*points)[i])[1],0.0);
	std::vector<GeoLib::Polyline*> *new_lines (copyPolylinesVector(this->_geo_objects.getPolylineVec(this->_geo_name), new_points));

	GeoLib::Grid<GeoLib::Point> grid(new_points->begin(), new_points->end());
	double max_segment_length (this->getMaxSegmentLength(*new_lines));
	max_segment_length *= max_segment_length; // squared so it can be compared to the squared distances calculated later
	
	const unsigned nMeshNodes ( mesh->getNNodes() );	
	std::vector<int> closest_geo_point(nMeshNodes); // index of closest geo point for each mesh node in (x,y)-plane
	std::vector<double> dist(nMeshNodes);  // distance between geo points and mesh nodes in (x,y)-plane
	for (size_t i=0; i<nMeshNodes; ++i)
	{
		const double zero_coords[3] = {(* mesh->getNode(i))[0], (* mesh->getNode(i))[1], 0.0};
		GeoLib::Point* pnt = grid.getNearestPoint(zero_coords);
		dist[i] = MathLib::sqrDist(pnt->getCoords(), zero_coords);
		closest_geo_point[i] = (dist[i]<=max_segment_length) ? getIndexInPntVec(pnt, new_points) : -1;
	}
	
	// store for each point the line segment to which it was added.
	const size_t nLines (new_lines->size());
	std::vector< std::vector<unsigned> > line_segment_map(nLines);
	for (std::size_t i=0; i<nLines; ++i)
	{
		line_segment_map[i] = std::vector<unsigned>((*new_lines)[i]->getNumberOfPoints(),0);
		std::iota(line_segment_map[i].begin(), line_segment_map[i].end(), 0);
	}

	for (std::size_t i=0; i<nMeshNodes; ++i)
	{
		// if mesh node too far away or exactly at point position
		if (closest_geo_point[i] == -1 || dist[i] < eps) continue; 

		const MeshLib::Node* node (mesh->getNode(i));
		for (std::size_t l=0; l<nLines; ++l)
		{
			// find relevant polylines
			if (!(*org_lines)[l]->isPointIDInPolyline(closest_geo_point[i])) continue;
			
			// find point position of closest geo point in original polyline
			GeoLib::Polyline* ply ((*org_lines)[l]);
			std::size_t nLinePnts ( ply->getNumberOfPoints() );
			std::size_t node_index_in_ply (0);
			for (node_index_in_ply=0; node_index_in_ply<nLinePnts; ++node_index_in_ply)
				if (ply->getPoint(node_index_in_ply) == (*points)[closest_geo_point[i]])
					break;
			const GeoLib::Point* geo_point (ply->getPoint(node_index_in_ply));

			// check if line segments connected to closest geo point intersect connected elements of current node
			const std::vector<MeshLib::Element*> elements (node->getElements());
			const std::size_t nElems = elements.size();
			for (std::size_t e=0; e<nElems; ++e)
			{
				const unsigned nEdges (elements[e]->getNEdges());
				unsigned intersection_count (0);

				for (unsigned n=0; n<nEdges; ++n)
				{
					if (intersection_count>1) break; //already two intersections

					const MeshLib::Element* line = elements[e]->getEdge(n);
					unsigned index_offset(0); // default: add to first line segment
					GeoLib::Point* intersection (NULL);
					if (node_index_in_ply>0) // test line segment before closest point
						intersection = calcIntersection(line->getNode(0), line->getNode(1), geo_point, ply->getPoint(node_index_in_ply-1));
					if (intersection == NULL && node_index_in_ply<(nLinePnts-1)) // test line segment after closest point
					{
						intersection = calcIntersection(line->getNode(0), line->getNode(1), geo_point, ply->getPoint(node_index_in_ply+1));
						index_offset = 1; // add to second segment
					}
					if (intersection)
					{
						intersection_count++;
						unsigned start_point_idx = static_cast<unsigned>(std::distance(line_segment_map[l].begin(), std::find_if(line_segment_map[l].begin(), line_segment_map[l].end(), [&node_index_in_ply, &index_offset](unsigned a){return a==node_index_in_ply+index_offset-1;})));
						unsigned end_point_idx   = static_cast<unsigned>(std::distance(line_segment_map[l].begin(), std::find_if(line_segment_map[l].begin(), line_segment_map[l].end(), [&node_index_in_ply, &index_offset](unsigned a){return a==node_index_in_ply+index_offset;})));
						std::size_t pos = getPointPosInLine((*new_lines)[l], start_point_idx, end_point_idx, intersection, eps);

						if (pos)
						{
							const std::size_t pnt_pos (new_points->size());
							new_points->push_back(intersection);
							(*new_lines)[l]->insertPoint(pos, pnt_pos);
							line_segment_map[l].insert(line_segment_map[l].begin()+pos, node_index_in_ply+index_offset-1);
						}
					}
				}
			}
		}
	}

	this->_geo_objects.addPointVec(new_points, const_cast<std::string&>(new_geo_name));
	std::vector<size_t> pnt_id_map = this->_geo_objects.getPointVecObj(new_geo_name)->getIDMap();
	for (std::size_t i=0; i<new_lines->size(); ++i)
		(*new_lines)[i]->updatePointIDs(pnt_id_map);
	this->_geo_objects.addPolylineVec(new_lines, new_geo_name);

	// map new geometry incl. additional point using the normal mapping method
	this->_geo_name = new_geo_name;
	this->mapOnMesh(mesh);
}