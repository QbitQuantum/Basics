void TabletopSegmentor::straightenPoints(PointCloudType &points, const tf::Transform& table_plane_trans, 
		      const tf::Transform& table_plane_trans_flat)
{
  tf::Transform trans = table_plane_trans_flat * table_plane_trans.inverse();
  pcl_ros::transformPointCloud(points, points, trans);
}