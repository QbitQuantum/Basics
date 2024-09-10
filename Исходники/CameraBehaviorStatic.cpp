bool intersectsTerrain(Vector3 a, Vector3 b)
{
	int steps = std::max(10.0f, a.distance(b));
	for (int i=0; i<steps; i++)
	{
		Vector3 pos = a + (b - a) * (float)i / steps;
		float y = a.y + (b.y - a.y) * (float)i / steps;
		float h = gEnv->terrainManager->getHeightFinder()->getHeightAt(pos.x, pos.z);
		if (h > y)
		{
			return true;
		}
	}
	return false;
}