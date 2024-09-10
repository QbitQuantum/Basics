double FEI2dLineLin :: edgeEvalNormal(FloatArray &normal, int iedge, const FloatArray &lcoords, const FEICellGeometry &cellgeo)
{
    normal.resize(2);
    normal.at(1) = cellgeo.giveVertexCoordinates(2)->at(xind) - cellgeo.giveVertexCoordinates(1)->at(xind);
    normal.at(2) = -(cellgeo.giveVertexCoordinates(2)->at(yind) - cellgeo.giveVertexCoordinates(1)->at(yind));
    return normal.normalize()*0.5;
}