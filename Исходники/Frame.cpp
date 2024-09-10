  // translate kpts by 6DOF transformation of frame
  void Frame::setTKpts(Eigen::Vector4d trans, Eigen::Quaterniond rot)
  {
    Vector3d tr;
    tr = trans.head<3>();
    // set up 3x4 transformation from kpt+disp to kpt
    Matrix4d Q;
    Q << 1.0, 0.0, 0.0, -cam.cx, // fy should enter in here somewhere...
         0.0, 1.0, 0.0, -cam.cy,
         0.0, 0.0, 0.0, cam.fx,
         0.0, 0.0, 1.0/cam.tx, 0;
    Matrix<double,3,4> P;
    P << cam.fx, 0.0, cam.cx, 0.0,
         0.0, cam.fx, cam.cy, 0.0,
         0.0, 0.0, 1.0, 0.0;
    // 3D point transform - inverse of frame motion
    Matrix4d T;
    T.setZero();
    Matrix3d R = rot.toRotationMatrix();
    T.block<3,3>(0,0) = R.transpose();
    T.block<3,1>(0,3) = -R*tr;
    T(3,3) = 1.0;
    
    P = P*T*Q;

    // go through points and set up transformed ones
    tkpts.resize(kpts.size());
    Vector4d v(0.0,0.0,0.0,1.0);
    for (int i=0; i<(int)kpts.size(); i++)
      {
        Vector3d vk;
        v(0) = kpts[i].pt.x;
        v(1) = kpts[i].pt.y;
        v(2) = disps[i];
        vk = P*v;
        tkpts[i].pt.x = vk(0)/vk(2);
        tkpts[i].pt.y = vk(1)/vk(2);
      }
  }