void 
pcl::gpu::RayCaster::run(const TsdfVolume& volume, const Affine3f& camera_pose)
{  
  camera_pose_.linear() = camera_pose.linear();
  camera_pose_.translation() = camera_pose.translation();
  volume_size_ = volume.getSize();
  device::Intr intr (fx_, fy_, cx_, cy_);

  vertex_map_.create(rows * 3, cols);
  normal_map_.create(rows * 3, cols);

  typedef Matrix<float, 3, 3, RowMajor> Matrix3f;
    
  Matrix3f R = camera_pose_.linear();
  Vector3f t = camera_pose_.translation();

  const  Mat33& device_R   = device_cast<const Mat33>(R);
  const float3& device_t   = device_cast<const float3>(t);
  
  float tranc_dist = volume.getTsdfTruncDist();  
  device::raycast (intr, device_R, device_t, tranc_dist, device_cast<const float3>(volume_size_), volume.data(), vertex_map_, normal_map_);  
}