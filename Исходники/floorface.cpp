void FloorFace::onAllLoaded() {
	Object::onAllLoaded();
	Floor *floor = Object::cast<Floor>(_parent);

	for (uint i = 0; i < ARRAYSIZE(_indices); i++) {
		_vertices[i] = floor->getVertex(_indices[i]);
	}
}