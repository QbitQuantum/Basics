 bool FootstepGraph::isCollidingBox(const Eigen::Affine3f& c, pcl::PointIndices::Ptr candidates) const
 {
   const pcl::PointCloud<pcl::PointXYZ>::ConstPtr input_cloud = obstacle_tree_model_->getInputCloud();
   Eigen::Affine3f inv_c = c.inverse();
   for (size_t i = 0; i < candidates->indices.size(); i++) {
     int index = candidates->indices[i];
     const pcl::PointXYZ candidate_point = input_cloud->points[index];
     // convert candidate_point into `c' local representation.
     const Eigen::Vector3f local_p = inv_c * candidate_point.getVector3fMap();
     if (std::abs(local_p[0]) < collision_bbox_size_[0] / 2 &&
         std::abs(local_p[1]) < collision_bbox_size_[1] / 2 &&
         std::abs(local_p[2]) < collision_bbox_size_[2] / 2) {
       return true;
     }
   }
   return false;
 }