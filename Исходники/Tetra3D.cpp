void Tetra3D::compute_mapped_coordinate(const CoordsT& coord, const NodesT& nodes, MappedCoordsT& mapped_coord)
{
  RealMatrix3 M;
  M.col(0) = nodes.row(1) - nodes.row(0);
  M.col(1) = nodes.row(2) - nodes.row(0);
  M.col(2) = nodes.row(3) - nodes.row(0);

  mapped_coord.noalias() = M.inverse() * (coord - nodes.row(0).transpose());
}