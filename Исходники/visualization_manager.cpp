void 
RGBID_SLAM::VisualizationManager::getPointCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr whole_point_cloud)
{  
  IdToPoseMap::iterator id2pose_map_it;        
  IdToPointCloudMap::const_iterator id2pointcloud_map_it;
  
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr aux_point_cloud;  
  aux_point_cloud.reset(new pcl::PointCloud<pcl::PointXYZRGB>);
  
  for (id2pose_map_it = id2pose_map_.begin(); 
       id2pose_map_it != id2pose_map_.end();
       id2pose_map_it++)
  {
    int kf_id = (*id2pose_map_it).first;
    Eigen::Affine3d pose = (*id2pose_map_it).second;
    
    id2pointcloud_map_it = id2pointcloud_map_.find(kf_id);
    
    if (id2pointcloud_map_it != id2pointcloud_map_.end())
    {
      aux_point_cloud->clear();
      copyPointCloud((*id2pointcloud_map_it).second, aux_point_cloud);  
      (*id2pointcloud_map_it).second->clear();
      alignPointCloud(aux_point_cloud, pose.linear(), pose.translation());   
      *whole_point_cloud += *aux_point_cloud;
    }          
  }  
  
  
}