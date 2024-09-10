double
FEI2dQuadLin :: edgeEvalNormal(FloatArray &answer, int iedge, const FloatArray &lcoords, const FEICellGeometry &cellgeo)
{
    int nodeA, nodeB;
    IntArray edgeNodes;
    this->computeLocalEdgeMapping(edgeNodes, iedge);
    nodeA = edgeNodes.at(1);
    nodeB = edgeNodes.at(2);

    answer.resize(2);
    answer.at(1) = -(cellgeo.giveVertexCoordinates(nodeB)->at(yind) - cellgeo.giveVertexCoordinates(nodeA)->at(yind) );
    answer.at(2) =  (cellgeo.giveVertexCoordinates(nodeB)->at(xind) - cellgeo.giveVertexCoordinates(nodeA)->at(xind) );
    return answer.normalize() * 0.5;
}