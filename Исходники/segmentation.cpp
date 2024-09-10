void pairAlign(const PointCloud::Ptr cloud_src, const PointCloud::Ptr cloud_tgt, 
    PointCloud::Ptr output, Eigen::Matrix4f &final_transform, bool downsample = false)
{
  PointCloud::Ptr src(new PointCloud);
  PointCloud::Ptr tgt(new PointCloud);
  pcl::VoxelGrid<PointType> grid;
  if(downsample)
  {
    grid.setLeafSize(0.05, 0.05, 0.05);
    grid.setInputCloud(cloud_src);
    grid.filter(*src);

    grid.setInputCloud(cloud_tgt);
    grid.filter(*tgt);
  }
  else
  {
    src = cloud_src;
    tgt = cloud_tgt;
  }

  PointCloudWithNormals::Ptr points_with_normals_src (new PointCloudWithNormals);
  PointCloudWithNormals::Ptr points_with_normals_tgt (new PointCloudWithNormals);

  pcl::NormalEstimation<PointType, PointNormalT> norm_est;
  pcl::search::KdTree<PointType>::Ptr tree(new pcl::search::KdTree<PointType> ());
  norm_est.setSearchMethod(tree);
  norm_est.setKSearch(30);

  norm_est.setInputCloud(src);
  norm_est.compute(*points_with_normals_src);
  pcl::copyPointCloud(*src, *points_with_normals_src);

  norm_est.setInputCloud(tgt);
  norm_est.compute(*points_with_normals_tgt);
  pcl::copyPointCloud(*tgt, *points_with_normals_tgt);

  PointRep point_representation;
  float alpha[4] = {1.0, 1.0, 1.0, 1.0};
  point_representation.setRescaleValues(alpha);

  pcl::IterativeClosestPointNonLinear<PointNormalT, PointNormalT> reg;
  reg.setTransformationEpsilon(1e-5);
  reg.setMaxCorrespondenceDistance(0.15);
  reg.setPointRepresentation(boost::make_shared<const PointRep> (point_representation));

  reg.setInputCloud(points_with_normals_src);
  reg.setInputTarget(points_with_normals_tgt);

  //Optimize
  Eigen::Matrix4f Ti = Eigen::Matrix4f::Identity(), prev, targetToSource;
  PointCloudWithNormals::Ptr reg_result = points_with_normals_src;
  reg.setMaximumIterations(2);

  for(int i = 0; i < 300; ++i)
  {
    points_with_normals_src = reg_result;

    reg.setInputCloud(points_with_normals_src);
    reg.align(*reg_result);

    Ti = reg.getFinalTransformation() * Ti;

    if(fabs ((reg.getLastIncrementalTransformation() - prev).sum()) < 
        reg.getTransformationEpsilon())
      reg.setMaxCorrespondenceDistance(reg.getMaxCorrespondenceDistance() - 0.001);

    prev = reg.getLastIncrementalTransformation();

    //showCloudsRight(points_with_normals_tgt, points_with_normals_src);
    std::cout << "Fitness: " << reg.getFitnessScore() << std::endl;
  }

  targetToSource = Ti.inverse();

  pcl::transformPointCloud(*cloud_tgt, *output, targetToSource);
  p->removePointCloud ("source");
  p->removePointCloud ("target");

  PointCloudColorHandlerCustom<PointType> cloud_tgt_h (output, 0, 255, 0);
  PointCloudColorHandlerCustom<PointType> cloud_src_h (cloud_src, 255, 0, 0);
  p->addPointCloud (output, cloud_tgt_h, "target", vp_2);
  p->addPointCloud (cloud_src, cloud_src_h, "source", vp_2);

  PCL_INFO ("Press q to continue the registration.\n");
  p->spinOnce ();

  *output += *cloud_src;
  final_transform = targetToSource;
}