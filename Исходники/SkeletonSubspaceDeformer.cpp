void SkeletonSubspaceDeformer::calculateSubspaceP()
{
	unsigned i, j, n, nj, vstart;
	Matrix44F spaceInv;
	Vector3F p;
	for(i = 0; i < numVertices(); i++) {
		p = getDeformedP()[i];
		n = m_jointIds[i]._ndim;
		nj = n - 1;
		vstart = m_jointIds[i][nj];
		
		for(j = 0; j < nj; j++) {
			SkeletonJoint * joint = m_skeleton->jointByIndex(m_jointIds[i][j]);
			spaceInv = joint->worldSpace();
			spaceInv.inverse();
			m_subspaceP[vstart + j] = spaceInv.transform(p);
		}
	}
}