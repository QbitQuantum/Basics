void App::doWork(){

  std::vector<float> xA;
  std::vector<float> yA;
  readCSVFile(cl_cfg_.filenameA, xA, yA);
  std::cout << xA.size() << " points in File A\n";
  lidarOdom_->doOdometry(xA, yA, xA.size(), 0);

  // Match second scan without a prior
  std::string i;
  cout << "Match B: Continue? ";
  cin >> i;

  std::vector<float> xB;
  std::vector<float> yB;
  readCSVFile(cl_cfg_.filenameB, xB, yB);
  std::cout << xB.size() << " points in File B\n";
  lidarOdom_->doOdometry(xB, yB, xB.size(), 1);

  // Match third scan giving a prior rotation for the heading
  // this alignment would otherwise fail:
  cout << "Match C: Continue? ";
  cin >> i;

  std::vector<float> xC;
  std::vector<float> yC;
  readCSVFile(cl_cfg_.filenameC, xC, yC);
  std::cout << xC.size() << " points in File C\n";

  ScanTransform prior;
  prior.x = 0;
  prior.y = 0;
  prior.theta = 1.7;
  lidarOdom_->doOdometry(xC, yC, xC.size(), 2, &prior);



  // 2. Determine the body position using the LIDAR motion estimate:
  Eigen::Isometry3d pose = lidarOdom_->getCurrentPose();
  Eigen::Quaterniond orientation(pose.rotation());

  Eigen::Vector3d rpy = orientation.matrix().eulerAngles(0,1,2);

  std::cout << "\n";
  std::cout << "x,y,yaw (m,m,deg): "<< pose.translation().x() << ", " << pose.translation().y()
            << ", "
            << rpy[2]*180/M_PI << "\n";
}