// Retun the normal for an arbitary polygon
Vector3d PolygonNormal(Vector3d polyData[]) {
	// Construct a normal for this polygon
	Vector3d v1 = polyData[0] - polyData[1];
	Vector3d v2 = polyData[1] - polyData[2];

	Vector3d normal;
	normal = Vector3d::CrossProduct(v1, v2);

	// Make sure this normal is a unit vector
	normal.Normalize();

	return normal;
}