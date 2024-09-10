vector<QVector3D> LayeredHairMesh::internalForces(const vector<QVector3D> &state) const
{
	vector<QVector3D> ifs(state.size(), QVector3D());
	float ks(5), kd(2), ko(1);
	int compSize = state.size() / 2;
	float lenSeg = compSize / seg;
	for (int i = 4; i < compSize; i ++)
	{
		// Spring restriction
		QVector3D dir = state[i - 4] - state[i];
		float deltaLen = dir.length() - restLen[i];
		dir.normalize();// *deltaLen;
		QVector3D fs = ks * dir * deltaLen;
		QVector3D fd = kd *
			QVector3D::dotProduct(
			state[i - 4 + compSize] - state[i + compSize], dir) * dir;

		// Constrant to original mesh
		float segU = (1 - (float)(i / seg) / lenSeg);
		QVector3D distDir = (points[i] - state[i]) * ko;

		ifs[i] = state[i + compSize];
		ifs[i + compSize] += fs + fd - state[i + compSize] * 0.1 + distDir;
		ifs[i - 4 + compSize] -= fs + fd;
	}
	for (int i = 0; i < 4; i++)
	{
		ifs[i] = QVector3D();
		ifs[i + compSize] = QVector3D();
	}
	return ifs;
}