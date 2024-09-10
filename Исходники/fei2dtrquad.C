double FEI2dTrQuad :: edgeEvalNormal(FloatArray &normal, int iedge, const FloatArray &lcoords, const FEICellGeometry &cellgeo)
{
    IntArray edgeNodes;
    this->computeLocalEdgeMapping(edgeNodes, iedge);
    double xi = lcoords(0);
    double dN1dxi = -0.5 + xi;
    double dN2dxi =  0.5 + xi;
    double dN3dxi = -2.0 * xi;

    normal.resize(2);

    normal.at(1) = dN1dxi * cellgeo.giveVertexCoordinates( edgeNodes.at(1) )->at(yind) +
    dN2dxi *cellgeo.giveVertexCoordinates( edgeNodes.at(2) )->at(yind) +
    dN3dxi *cellgeo.giveVertexCoordinates( edgeNodes.at(3) )->at(yind);

    normal.at(2) = -dN1dxi *cellgeo.giveVertexCoordinates( edgeNodes.at(1) )->at(xind) +
    - dN2dxi *cellgeo.giveVertexCoordinates( edgeNodes.at(2) )->at(xind) +
    - dN3dxi *cellgeo.giveVertexCoordinates( edgeNodes.at(3) )->at(xind);

    return normal.normalize();
}