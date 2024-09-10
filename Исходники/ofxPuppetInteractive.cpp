float getNearestVertex(const ofMesh& mesh, const ofVec2f& target, int& vertexIndex) {
	float bestDistance = 0;
	for(int i = 0; i < mesh.getNumVertices(); i++) {
		float distance = target.distance(mesh.getVertex(i));
		if(distance < bestDistance || i == 0) {
			bestDistance = distance;
			vertexIndex = i;
		}
	}
	return bestDistance;
}