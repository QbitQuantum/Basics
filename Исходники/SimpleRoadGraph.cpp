void SimpleRoadGraph::_generateMeshVertices(ucore::TextureManager* textureManager) {
	ucore::RenderableQuadList* renderable = new ucore::RenderableQuadList(textureManager->get("data/textures/street.jpg"));

	roadGraphEdgeIter ei, eend;
	for (boost::tie(ei, eend) = boost::edges(myRoadGraph); ei != eend; ++ei) {
		SimpleRoadGraphEdge* edge = &myRoadGraph[*ei];

		QVector3D pt1 = myRoadGraph[boost::source(*ei, myRoadGraph)].getPt();
		QVector3D pt2 = myRoadGraph[boost::target(*ei, myRoadGraph)].getPt();

		QVector3D vec = pt2 - pt1;
		vec = QVector3D(-vec.y(), vec.x(), 0.0f);
		vec.normalize();

		QVector3D p0 = pt1 + vec * edge->getWidth() / 2.0f + QVector3D(0, 0, heightAboveGround);
		QVector3D p1 = pt1 - vec * edge->getWidth() / 2.0f + QVector3D(0, 0, heightAboveGround);
		QVector3D p2 = pt2 - vec * edge->getWidth() / 2.0f + QVector3D(0, 0, heightAboveGround);
		QVector3D p3 = pt2 + vec * edge->getWidth() / 2.0f + QVector3D(0, 0, heightAboveGround);
		QVector3D normal = ucore::Util::calculateNormal(p0, p1, p2);

		//renderable2->addQuad(p0, p1, p2, p3, normal, color);
		renderable->addQuad(p0, p1, p2, p3, normal, 0, 1, 0, 1);
	}

	renderables.push_back(renderable);
}