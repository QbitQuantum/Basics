/*
 * Calculates a Catmull Clark Edgepoint.
 */
Vertex GeometryOps::getEdgePoint(Edge* edg,Face*fptr,int i,Edge * eptr,int j){
	Vertex edgePoint = Vertex();
	GeometryOps::twoFace touchingFaces;
	touchingFaces = getOtherFace(*edg,fptr,i);

	edgePoint.add(*edg->getVertexA());
	edgePoint.add(*edg->getVertexB());
	//edgePoint.add(edg->getEdgeMidPoint());
	edgePoint.add(touchingFaces.faceOne.getCentroid());
	edgePoint.add(touchingFaces.faceTwo.getCentroid());
	//cout << "EdgePoint Added" << vertexToString(edgePoint)<<endl;
	edgePoint.div(4.0f);
	//edgePoint.div(3.0f);
	//cout << "Edgepoint: \t" << vertexToString(edgePoint)<<"\n"<<endl;
	return edgePoint;
}