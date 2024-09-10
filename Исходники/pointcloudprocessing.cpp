void PointCloudProcessing::getRTGeometricLinearSystem(PointCloudC::Ptr corrRef,
                                                      PointCloudC::Ptr corrNew,
                                                      Eigen::Matrix4f &transMat)
{
  // build linear system Ax = b;
  int rows = 3*corrRef->points.size();
  int cols = 6;
  Eigen::MatrixXf A(rows, cols); A.setZero();
  Eigen::MatrixXf b(rows, 1); b.setZero();
  for(int i=0; i<corrRef->points.size(); i++)
    {
      float X1 = corrRef->points.at(i).x;
      float Y1 = corrRef->points.at(i).y;
      float Z1 = corrRef->points.at(i).z;
      float X0 = corrNew->points.at(i).x;
      float Y0 = corrNew->points.at(i).y;
      float Z0 = corrNew->points.at(i).z;
      A(3*i,   0) = 0;      A(3*i,   1) = Z0+Z1;  A(3*i,   2) = -Y0-Y1; A(3*i,   3) = 1;
      A(3*i+1, 0) = -Z0-Z1; A(3*i+1, 1) = 0;      A(3*i+1, 2) = X0+X1;  A(3*i+1, 4) = 1;
      A(3*i+2, 0) = Y0+Y1;  A(3*i+1, 1) = -X0-X1; A(3*i+2, 2) = 0;      A(3*i+2, 5) = 1;

      b(3*i,   0) = X1-X0;
      b(3*i+1, 0) = Y1-Y0;
      b(3*i+2, 0) = Z1-Z0;
    }
  //    std::cout<<"A = "<<A<<std::endl;
  //    std::cout<<"b = "<<b<<std::endl;
  Eigen::MatrixXf solveX(rows, 1); solveX.setZero();
  solveX = A.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b);
  //    std::cout<<"solveX: "<<solveX<<"\n";

  // solveX = [Rx, Ry, Rz, T'x, T'y, T'z];
  Eigen::Matrix3f I_Vx; I_Vx.setOnes();
  I_Vx(0,0) = 1;          I_Vx(0,1) = solveX(2);  I_Vx(0,2) = -solveX(1);
  I_Vx(1,0) = -solveX(2); I_Vx(1,1) = 1;          I_Vx(1,2) = solveX(0);
  I_Vx(2,0) = solveX(1);  I_Vx(2,1) = -solveX(0); I_Vx(2,2) = 1;
  Eigen::Vector3f Tx; Tx.setZero();
  Tx(0) = solveX(3); Tx(1) = solveX(4); Tx(2) = solveX(5);
  Eigen::Vector3f tx; tx.setZero();
  tx = I_Vx.inverse()*Tx;
  transMat(0,3) = tx(0); transMat(1,3) = tx(1); transMat(2,3) = tx(2);

  Eigen::Matrix3f IplusVx; IplusVx.setOnes();
  IplusVx(0,0) = 1;          IplusVx(0,1) = -solveX(2);  IplusVx(0,2) = solveX(1);
  IplusVx(1,0) = solveX(2);  IplusVx(1,1) = 1;           IplusVx(1,2) = -solveX(0);
  IplusVx(2,0) = -solveX(1); IplusVx(2,1) = solveX(0);   IplusVx(2,2) = 1;
  Eigen::Matrix3f Ro; Ro.setZero();
  Ro = I_Vx.inverse()*IplusVx;
  transMat(0,0) = Ro(0,0); transMat(0,1) = Ro(0,1); transMat(0,2) = Ro(0,2); transMat(0,3) = tx(0);
  transMat(1,0) = Ro(1,0); transMat(1,1) = Ro(1,1); transMat(1,2) = Ro(1,2); transMat(1,3) = tx(1);
  transMat(2,0) = Ro(2,0); transMat(2,1) = Ro(2,1); transMat(2,2) = Ro(2,2); transMat(2,3) = tx(2);
  //    std::cout<<"transMat Geometric: "<<transMat<<"\n";
}