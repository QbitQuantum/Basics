static void relaxEndPoint(const Vertex &curNodePos,
                          const DijkstraNode::ConstIter &curNodeIter,
                          const Vertex &endPointPos,
                          DijkstraNode &endPoint,
                          const Region &region) {
	if (region.isLineOfSight(curNodePos, endPointPos)) {
		int totalCost = (*curNodeIter).cost + curNodePos.distance(endPointPos);
		if (totalCost < endPoint.cost) {
			endPoint.parentIter = curNodeIter;
			endPoint.cost = totalCost;
		}
	}
}