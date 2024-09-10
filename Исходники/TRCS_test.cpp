int
main (int argc, char** argv)
{
  srand ((unsigned int) time (NULL));
  time_t start, end;
  double dift;

  float resolution = 5.0f;

  pcl::SegmentDifferences<PointT> sd;
    
  pcl::PointCloud<PointT>::Ptr cloudA (new pcl::PointCloud<PointT>); 

  time(&start);
  cloudA->width = 128;
  cloudA->height = 1;
  cloudA->points.resize (cloudA->width * cloudA->height);  
  for (size_t i = 0; i < cloudA->points.size (); ++i)
  {
    cloudA->points[i].x = 64.0f * rand () / (RAND_MAX + 1.0f);
    cloudA->points[i].y = 64.0f * rand () / (RAND_MAX + 1.0f);
    cloudA->points[i].z = 64.0f * rand () / (RAND_MAX + 1.0f);
	cloudA->points[i].intensity = rand () / 255 + 1.0f;
  }
  time(&end);

  dift = difftime (end,start);
  std::cout<<"It took "<<dift<<" secs to read in the first point cloud"<<std::endl;
  
  pcl::PointCloud<PointT>::Ptr cloudB (new pcl::PointCloud<PointT>);

  time(&start);
  cloudB->width = 128;
  cloudB->height = 1;
  cloudB->points.resize (cloudB->width * cloudB->height);
  for (size_t i = 0; i < cloudB->points.size (); ++i)
  {
    cloudB->points[i].x = 64.0f * rand () / (RAND_MAX + 1.0f);
    cloudB->points[i].y = 64.0f * rand () / (RAND_MAX + 1.0f);
    cloudB->points[i].z = 64.0f * rand () / (RAND_MAX + 1.0f);
	cloudB->points[i].intensity = rand () / 255 + 1.0f;
  }
  time(&end);

  dift = difftime (end,start);
  std::cout<<"It took "<<dift<<" secs to read in the second point cloud"<<std::endl;
 

  pcl::PointCloud<PointT> cloudC;
  cloudC.width = 0;
  cloudC.height = 0;
  cloudC.points.resize (cloudC.width * cloudC.height);

  pcl::search::KdTree<PointT>::Ptr kdtree(new pcl::search::KdTree<PointT>);
  kdtree->setInputCloud(cloudB);
  sd.setDistanceThreshold (resolution);
  sd.setInputCloud (cloudA);
  sd.setTargetCloud (cloudB);
  sd.setSearchMethod (kdtree);  
  sd.segmentInt (cloudC);

  std::cout<<"The points in cloudC are "<<std::endl;
  for (size_t i = 0; i < cloudC.points.size (); ++i)
  {
	std::cout<<cloudC.points[i].x<<" "<<cloudC.points[i].y<<" "<<cloudC.points[i].z<<" "<<cloudC.points[i].intensity<<std::endl;
  }
  system("pause");
}