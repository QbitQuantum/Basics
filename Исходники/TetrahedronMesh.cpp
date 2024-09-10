void TetrahedronMesh::InitMesh()
{
  UpdateMesh();

  // Find min tet volume
  double minVol = std::numeric_limits<double>::max();
  for(int t=0;t<Tetrahedra->rows();t++)
  {
    Eigen::Vector3d A = InitalVertices->row(Tetrahedra->coeff(t,0)).cast<double>();
    Eigen::Vector3d B = InitalVertices->row(Tetrahedra->coeff(t,1)).cast<double>();
    Eigen::Vector3d C = InitalVertices->row(Tetrahedra->coeff(t,2)).cast<double>();
    Eigen::Vector3d D = InitalVertices->row(Tetrahedra->coeff(t,3)).cast<double>();

    Eigen::Vector3d a = A-D;
    Eigen::Vector3d b = B-D;
    Eigen::Vector3d c = C-D;

    double vol = a.dot(c.cross(b));

    if(vol < minVol)
      minVol = vol;
  }

  EPS1 = 10e-5;
  EPS3 = minVol*EPS1;
}