void TerrainGesture::UpdateKeyOrbit(double secondsSinceLastUpdate)
{
	if (_keyOrbitLeft) _keyOrbitMomentum -= 32 * (float)secondsSinceLastUpdate;
	if (_keyOrbitRight) _keyOrbitMomentum += 32 * (float)secondsSinceLastUpdate;

	TerrainView* terrainView = _hotspot->GetTerrainView();
	glm::vec2 centerScreen = terrainView->GetTerrainViewport().NormalizedToLocal(glm::vec2{});
	glm::vec3 contentAnchor = terrainView->GetTerrainPosition3(centerScreen);
	terrainView->Orbit(contentAnchor, (float)secondsSinceLastUpdate * _keyOrbitMomentum);

	_keyOrbitMomentum *= exp2f(-25 * (float)secondsSinceLastUpdate);
}