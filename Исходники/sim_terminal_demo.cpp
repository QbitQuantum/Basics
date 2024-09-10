// A 'halo' camera - a circular ring of poses all pointing at a center point
// @param: focus_center: the center points
// @param: halo_r: radius of the ring
// @param: halo_dz: elevation of the camera above/below focus_center's z value
// @param: n_poses: number of generated poses
void
generate_halo(
  std::vector<Eigen::Isometry3d, Eigen::aligned_allocator<Eigen::Isometry3d> > &poses,
  Eigen::Vector3d focus_center,double halo_r,double halo_dz,int n_poses){
  
  for (double t=0;t < (2*M_PI);t =t + (2*M_PI)/ ((double) n_poses) ){
    double x = halo_r*cos(t);
    double y = halo_r*sin(t);
    double z = halo_dz;
    double pitch =atan2( halo_dz,halo_r); 
    double yaw = atan2(-y,-x);
   
    Eigen::Isometry3d pose;
    pose.setIdentity();
    Eigen::Matrix3d m;
    m = AngleAxisd(yaw, Eigen::Vector3d::UnitZ())
	* AngleAxisd(pitch, Eigen::Vector3d::UnitY())
	* AngleAxisd(0, Eigen::Vector3d::UnitZ());    

    pose *=m;
    Vector3d v(x,y,z);
    v += focus_center;
    pose.translation() = v;
    poses.push_back(pose);  
  }
  return ;
}