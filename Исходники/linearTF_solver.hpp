  // Assume t = double[3], q = double[4]
  void EstimateTfSVD(double* t, double* q)
  {
    // Assemble the correlation matrix H = target * reference'
    Eigen::Matrix3d H = (cloud_tgt_demean * cloud_ref_demean.transpose ()).topLeftCorner<3, 3>();

    // Compute the Singular Value Decomposition
    Eigen::JacobiSVD<Eigen::Matrix3d> svd (H, Eigen::ComputeFullU | Eigen::ComputeFullV);
    Eigen::Matrix3d u = svd.matrixU ();
    Eigen::Matrix3d v = svd.matrixV ();

    // Compute R = V * U'
    if (u.determinant () * v.determinant () < 0)
      {
	for (int i = 0; i < 3; ++i)
	  v (i, 2) *= -1;
      }

    //    std::cout<< "centroid_src: "<<centroid_src(0) <<" "<< centroid_src(1) <<" "<< centroid_src(2) << " "<< centroid_src(3)<<std::endl;
    //    std::cout<< "centroid_tgt: "<<centroid_tgt(0) <<" "<< centroid_tgt(1) <<" "<< centroid_tgt(2) << " "<< centroid_tgt(3)<<std::endl;
    
    Eigen::Matrix3d R = v * u.transpose ();

    const Eigen::Vector3d Rc (R * centroid_tgt.head<3> ());
    Eigen::Vector3d T = centroid_ref.head<3> () - Rc;

    // Make sure these memory locations are valid
    assert(t != NULL && q!=NULL);
    Eigen::Quaterniond Q(R);
    t[0] = T(0);  t[1] = T(1);  t[2] = T(2);
    q[0] = Q.w(); q[1] = Q.x(); q[2] = Q.y(); q[3] = Q.z();
  }