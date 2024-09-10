void QTPFSPathDrawer::DrawNodeTree(const MoveDef* md) const {
	QTPFS::QTNode* nt = pm->nodeTrees[md->pathType];
	CVertexArray* va = GetVertexArray();

	std::list<const QTPFS::QTNode*> nodes;
	std::list<const QTPFS::QTNode*>::const_iterator nodesIt;

	GetVisibleNodes(nt, nodes);

	va->Initialize();
	va->EnlargeArrays(nodes.size() * 4, 0, VA_SIZE_C);

	for (nodesIt = nodes.begin(); nodesIt != nodes.end(); ++nodesIt) {
		DrawNode(*nodesIt, md, va, false, true, true);
	}

	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	va->DrawArrayC(GL_QUADS);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
}