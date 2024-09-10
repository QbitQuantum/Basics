void Sector::shrink(float radius) {
	if ((getType() & WalkType) == 0 || _shrinkRadius == radius)
		return;

	_shrinkRadius = radius;
	if (!_origVertices) {
		_origVertices = _vertices;
		_vertices = new Math::Vector3d[_numVertices + 1];
	}

	// Move each vertex inwards by the given amount.
	for (int j = 0; j < _numVertices; j++) {
		Math::Vector3d shrinkDir;

		for (int k = 0; k < g_grim->getCurrSet()->getSectorCount(); k++) {
			Sector *other = g_grim->getCurrSet()->getSectorBase(k);
			if ((other->getType() & WalkType) == 0)
				continue;

			for (int l = 0; l < other->_numVertices; l++) {
				Math::Vector3d *otherVerts = other->_vertices;
				if (other->_origVertices)
					otherVerts = other->_origVertices;
				if ((otherVerts[l] - _origVertices[j]).getMagnitude() < 0.01f) {
					Math::Vector3d e1 = otherVerts[l + 1] - otherVerts[l];
					Math::Vector3d e2;
					if (l - 1 >= 0)
						e2 = otherVerts[l] - otherVerts[l - 1];
					else
						e2 = otherVerts[l] - otherVerts[other->_numVertices - 1];
					e1.normalize();
					e2.normalize();
					Math::Vector3d bisector = (e1 - e2);
					bisector.normalize();
					shrinkDir += bisector;
				}
			}
		}

		if (shrinkDir.getMagnitude() > 0.1f) {
			shrinkDir.normalize();
			_vertices[j] = _origVertices[j] + shrinkDir * radius;
		} else {
			_vertices[j] = _origVertices[j];
		}
	}

	_vertices[_numVertices] = _vertices[0];

	// Make sure the sector is still convex.
	for (int j = 0; j < _numVertices; j++) {
		Math::Vector3d e1 = _vertices[j + 1] - _vertices[j];
		Math::Vector3d e2;
		if (j - 1 >= 0)
			e2 = _vertices[j] - _vertices[j - 1];
		else
			e2 = _vertices[j] - _vertices[_numVertices - 1];

		if (e1.x() * e2.y() > e1.y() * e2.x()) {
			// Not convex, so mark the sector invalid.
			_invalid = true;
			delete[] _vertices;
			_vertices = _origVertices;
			_origVertices = nullptr;
			break;
		}
	}
}