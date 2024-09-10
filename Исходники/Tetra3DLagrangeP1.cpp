void Tetra3DLagrangeP1::mapped_coordinates(const CoordsT& coord, const NodeMatrixT& nodes, MappedCoordsT& mappedCoord)
{
  RealMatrix3 M;
  M.col(0) = nodes.row(1) - nodes.row(0);
  M.col(1) = nodes.row(2) - nodes.row(0);
  M.col(2) = nodes.row(3) - nodes.row(0);
  
  mappedCoord = M.inverse() * (coord - nodes.row(0).transpose());
}