void foot_contact_classify::determineContactPoints(int64_t utime, Eigen::Isometry3d primary_foot, Eigen::Isometry3d secondary_foot){
  // Currently Deprecated to remove PCL dependency

  //////////////////////////////////////////////////////////
  bool success =false;

  // use primary and secondary foot to determine plane that CPs are one
  Isometry3dTime null_pose = Isometry3dTime(utime, Eigen::Isometry3d::Identity() );
  pc_vis_->pose_to_lcm_from_list(2001, null_pose);

  // Determine moving contact points in stationary foot's sole frame:
  // I define the sole frame as a frame directly below the foot frame on the sole
  pronto::PointCloud* cp_moving(new pronto::PointCloud ());
  Eigen::Isometry3d foot_to_foot =  primary_foot.inverse() * secondary_foot * foot_to_sole_;
  pc_vis_->transformPointCloud(*contact_points_, *cp_moving, Eigen::Affine3f ( foot_to_foot.cast<float>() ) );
  pc_vis_->ptcld_to_lcm_from_list(2004, *cp_moving, utime, utime); // this is visualised relative to 0,0,0
  
  if (cp_moving_prev_->points.size() != 4){
    std::cout << "Previous contact points not four - we have a problem\n";
    success = false;
  }else{

    int n_points_in_contact = 0;
    for (size_t i=0; i < 4 ; i++){
      pronto::Point cp = cp_moving->points[i];
      pronto::Point cp_prev = cp_moving_prev_->points[i];

      double raise = fabs(cp.z);

      if ( raise < 0.02){
        n_points_in_contact++;
        //std::cout <<utime << " "<< raise << " " << (int)i << " cp in contact\n";
      }else{
        //std::cout <<utime << " "<< raise << " " << (int)i << " cp NOT in contact\n";
      }
    }

    if (n_points_in_contact >0){
      std::cout << utime << " " << n_points_in_contact << "\n";
    }



    success = true;
  }

  cp_moving_prev_ = cp_moving;
  

  // determine the velocity of the SF CPs onto the PFCP plane
  // infer the time to contact by differencing

  // If the distance of the foot to the plane is less than a certain amount
  // and the time to contact is less than a certain amount
  // then contact is likely
}