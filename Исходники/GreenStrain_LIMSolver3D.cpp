void GreenStrain_LIMSolver3D::prepareProblemData(std::vector<int>& hessRowIdx, std::vector<int>& hessColIdx)
{
  const int numNodes = mesh->InitalVertices->rows();

  // Compute deformation gradients
  int numTets = mesh->Tetrahedra->rows();
  Ms.resize(4,3*numTets);
  MMTs.resize(4,4*numTets);

  Eigen::Matrix<double,4,3> SelectorM;
  SelectorM.block<3,3>(0,0) = Eigen::Matrix3d::Identity();
  SelectorM.row(3) = Eigen::Vector3d::Ones()*-1;
  
  for(int t=0;t<numTets;t++)
  {
    Eigen::VectorXi indices = TetrahedronVertexIdx.col(t);

    Eigen::Vector3d A = mesh->InitalVertices->row(mesh->Tetrahedra->coeff(t,0)).cast<double>();
    Eigen::Vector3d B = mesh->InitalVertices->row(mesh->Tetrahedra->coeff(t,1)).cast<double>();
    Eigen::Vector3d C = mesh->InitalVertices->row(mesh->Tetrahedra->coeff(t,2)).cast<double>();
    Eigen::Vector3d D = mesh->InitalVertices->row(mesh->Tetrahedra->coeff(t,3)).cast<double>();

    Eigen::Matrix3d V;
    V << A-D,B-D,C-D;
    
    Eigen::Matrix<double,4,3> Mtemp = SelectorM*V.inverse().cast<double>();
    Ms.block<4,3>(0,3*t) = Mtemp;
    MMTs.block<4,4>(0,4*t) = Mtemp*Mtemp.transpose();
  }
}