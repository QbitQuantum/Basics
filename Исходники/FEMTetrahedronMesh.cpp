float FEMTetrahedronMesh::getTetraVolume(Vector3F e1, Vector3F e2, Vector3F e3) {
	return  e1.dot( e2.cross( e3 ) )/ 6.0f;
}