void MaxFlowVisualizer::showEdges(QPainter &painter) {
    for (VertexIndex vertex = 0; vertex < relabelToFrontAlgo.getNetwork().getVerticesNumber(); ++vertex) {
        auto adjacentEdgesList = relabelToFrontAlgo.getNetwork().getEdgesListFromVertex(vertex);
        for (Edge edge : adjacentEdgesList) {
            if (edge.getCapacity() != 0) {
                drawEdge(edge, painter);
            }
        }
    }
}