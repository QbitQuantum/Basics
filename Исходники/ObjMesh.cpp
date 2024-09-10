// ----------------------------------------------------------------------
void ObjMesh::updateNormals()
{
	mNormals.resize(mVertices.size());
	int i;
	for (i = 0; i < (int)mNormals.size(); i++) 
		mNormals[i].zero();
	NxVec3 n;
	for (i = 0; i < (int)mTriangles.size(); i++) {
		ObjMeshTriangle &mt = mTriangles[i];
		mt.normalNr[0] = mt.vertexNr[0];
		mt.normalNr[1] = mt.vertexNr[1];
		mt.normalNr[2] = mt.vertexNr[2];
		n.cross(mVertices[mt.vertexNr[1]] - mVertices[mt.vertexNr[0]], 
			mVertices[mt.vertexNr[2]] - mVertices[mt.vertexNr[0]]);
		mNormals[mt.normalNr[0]] += n;
		mNormals[mt.normalNr[1]] += n;
		mNormals[mt.normalNr[2]] += n;
	}
	for (i = 0; i < (int)mNormals.size(); i++) 
		mNormals[i].normalize();
}