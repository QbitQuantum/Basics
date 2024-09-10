	bool TerrainGroup::checkDistance(Vector3 position_to_check, float extra_range) {
		current_distance = position_to_check.distance(center);
		return (current_distance < extra_range);
	}