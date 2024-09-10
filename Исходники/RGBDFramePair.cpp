void RGBDFramePair::calTransFromFPoints(const vector<int>& index,MatrixXd& trans)
{
  Vector3d rCenter(0,0,0);
  Vector3d mCenter(0,0,0);
  Matrix3d mat;
  mat.setZero();
  int cSize=index.size();

  for (int j=0;j<cSize;j++)
  {
    rCenter+=refFPoints[index[j]];
    mCenter+=mainFPoints[index[j]];
  }
  rCenter/=cSize;
  mCenter/=cSize;

  for (int j=0;j<cSize;j++)
  {
    Vector3d r=refFPoints[index[j]];
    Vector3d m=mainFPoints[index[j]];
    mat+=(m-mCenter)*(r-rCenter).transpose();
  }
  HMatrix hmat;
  HMatrix	Q,S;
  copyHMatrix3D(hmat,mat);
  polar_decomp(hmat,Q,S);

  trans.resize(3,4);
  trans.setZero();
  MatrixXd trans3D(3,3);
  Vector3d translation;
  copyFromHMatrix3D(Q,trans3D);
  copyFromHMatrix3D(Q,trans);
  translation=mCenter-trans3D*rCenter;
  trans.col(3)=translation;

}