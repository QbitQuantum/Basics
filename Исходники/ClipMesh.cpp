bool ClipMesh::getTriangles( std::vector<int>& indices ) {
	const size_t numFaces = _faces.size();
	for( size_t currFace = 0; currFace < numFaces; ++currFace ) {
		CFace& face = _faces[currFace];
		if( !face.visible ) {
			continue;
		}

		const size_t numEdges = face.edges.size();
		//assert(numEdges >= 3); // unexpected condition
		if( numEdges < 3 ) {
			return false;
		}
		std::vector<int> vOrdered(numEdges+1);
		if( !orderVertices(face, vOrdered) ) {
			return false;
		}

		const int v0 = vOrdered[0];
		const int v2 = vOrdered[numEdges - 1];
		const int v1 = vOrdered[(numEdges - 1) >> 1];
		const cc::Vec3f diff1 = _vertices[v1].point - _vertices[v0].point;
		const cc::Vec3f diff2 = _vertices[v2].point - _vertices[v0].point;
		const float sgnVolume = face.normal.dot(diff1.cross(diff2));
		if( sgnVolume < 0.0f ) { // feel free to invert this test
			// clockwise, need to swap
			for( unsigned int i = 1; i + 1 < numEdges; ++i ) {
				indices.push_back(v0);
				indices.push_back(vOrdered[i + 1]);
				indices.push_back(vOrdered[i]);
			}
		} else {
			// counterclockwise
			for( unsigned int i = 1; i + 1 < numEdges; ++i ) {
				indices.push_back(v0);
				indices.push_back(vOrdered[i]);
				indices.push_back(vOrdered[i + 1]);
			}
		}
	}

	return true;
}