void GreenStrain_LIMSolver2D::prepareProblemData(std::vector<int>& hessRowIdx, std::vector<int>& hessColIdx)
{
  // Compute deformation gradients
  int numTets = mesh->Triangles->rows();
  Ms.resize(3,2*numTets);
  MMTs.resize(3,3*numTets);

  Eigen::Matrix<double,3,2> SelectorM;
  SelectorM.block<2,2>(0,0) = Eigen::Matrix<double,2,2>::Identity();
  SelectorM.row(2) = Eigen::Vector2d::Ones()*-1;
  
  for(int t=0;t<numTets;t++)
  {
    Eigen::Vector2d A,B,C;
    if(mesh->IsCorotatedTriangles)
    {
      A = mesh->CorotatedTriangles->row(t).block<1,2>(0,0).cast<double>();
      B = mesh->CorotatedTriangles->row(t).block<1,2>(0,2).cast<double>();
      C = mesh->CorotatedTriangles->row(t).block<1,2>(0,4).cast<double>();	
    }
    else
    {
      A = mesh->InitalVertices->row(mesh->Triangles->coeff(t,0)).block<1,2>(0,0).cast<double>();
      B = mesh->InitalVertices->row(mesh->Triangles->coeff(t,1)).block<1,2>(0,0).cast<double>();
      C = mesh->InitalVertices->row(mesh->Triangles->coeff(t,2)).block<1,2>(0,0).cast<double>();
    }

    Eigen::Matrix2d V;
    V << A-C,B-C;
    
    Eigen::Matrix<double,3,2> Mtemp = SelectorM*V.inverse().cast<double>();
    Ms.block<3,2>(0,2*t) = Mtemp;
    MMTs.block<3,3>(0,3*t) = Mtemp*Mtemp.transpose();
  }
}