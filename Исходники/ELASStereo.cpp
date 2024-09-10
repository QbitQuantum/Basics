ELASStereo::ELASStereo(calibu::CameraRig& rig, const unsigned int width,
                       const unsigned int height)
  : m_dDisparity(width, height), m_dDepth(width, height) {
  if (rig.cameras.size() != 2) {
    std::cerr << "Two camera models are required to run this program!"
              << std::endl;
    exit(1);
  }

  m_width = width;
  m_height = height;

  Eigen::Matrix3f CamModel0 = rig.cameras[0].camera.K().cast<float>();
  Eigen::Matrix3f CamModel1 = rig.cameras[1].camera.K().cast<float>();

  roo::ImageIntrinsics camMod[] = {
    {CamModel0(0, 0), CamModel0(1, 1), CamModel0(0, 2), CamModel0(1, 2)},
    {CamModel1(0, 0), CamModel1(1, 1), CamModel1(0, 2), CamModel1(1, 2)}};

  m_Kl = camMod[0][0].Matrix();

  // print selected camera model
  std::cout << "Camera Model used: " << std::endl << camMod[0][0].Matrix()
      << std::endl;

  Eigen::Matrix3d RDFvision;
  RDFvision << 1, 0, 0, 0, 1, 0, 0, 0, 1;
  Eigen::Matrix3d RDFrobot;
  RDFrobot << 0, 1, 0, 0, 0, 1, 1, 0, 0;
  Eigen::Matrix4d T_vis_ro = Eigen::Matrix4d::Identity();
  T_vis_ro.block<3, 3>(0, 0) = RDFvision.transpose() * RDFrobot;
  Eigen::Matrix4d T_ro_vis = Eigen::Matrix4d::Identity();
  T_ro_vis.block<3, 3>(0, 0) = RDFrobot.transpose() * RDFvision;

  const Sophus::SE3d T_rl =
      T_rlFromCamModelRDF(rig.cameras[0], rig.cameras[1], RDFvision);
  m_baseline = T_rl.translation().norm();

  std::cout << "Baseline is: " << m_baseline << std::endl;
}