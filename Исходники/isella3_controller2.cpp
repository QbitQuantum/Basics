/// Trajectory Planner
Vector6d Isella3Controller::Trajectory(double desired_pos, unsigned long time_in, unsigned long time_fin, int iArmModuleId, int iAxisId)
{    
  Vector6d b;
  Vector6d x;
  Eigen::Matrix<double, 6, 6> A;
  b << theApp.fGetAngleAxisIs(iArmModuleId,iAxisId), 0, 0, desired_pos, 0, 0;
  A << 1,time_in,pow(time_in,2),pow(time_in,3),pow(time_in,4),pow(time_in,5),
    0,1,2*time_in,3*pow(time_in,2),4*pow(time_in,3),5*pow(time_in,4),
    0,0,2,6*time_in,12*pow(time_in,2),20*pow(time_in,3),
    1,time_fin,pow(time_fin,2),pow(time_fin,3),pow(time_fin,4),pow(time_fin,5),
    0,1,2*time_fin,3*pow(time_fin,2),4*pow(time_fin,3),5*pow(time_fin,4),
    0,0,2,6*time_fin,12*pow(time_fin,2),20*pow(time_fin,3);
  x = A.inverse()*b;

  ROS_INFO("Trajectory ---> desired_pos = %d, AngleAxisIs = %d, time_in = %d, time_fin = %d", (int)desired_pos, (int)theApp.fGetAngleAxisIs(iArmModuleId,iAxisId), (int)time_in, (int)time_fin);
  std::cout << "Matrix A:\n" << A << "\nVector b:\n" << b << "\nVector x:\n" << x << "\nVector b = A*x:\n" << A*x << endl;

  return x;
}