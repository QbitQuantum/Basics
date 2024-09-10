void AccCorner::addCornerNeighborBetween(int a, int b, Vector3F * positions, Vector3F * normals)
{
	_cornerIndices.push_back(a);
	_cornerIndices.push_back(b);
	_tagCornerIndices.push_back(0);
	_tagCornerIndices.push_back(0);
	_cornerPositions.push_back(positions[a] * 0.5f + positions[b] * 0.5f);
	Vector3F an = normals[a] * 0.5f + normals[b] * 0.5f;
	an.normalize();
	_cornerNormals.push_back(an);
}