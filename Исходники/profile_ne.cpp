int
main (int argc, char** argv)
{
  if (argc < 2)
  {
    std::cerr << "Error: Please specify a PCD file (rosrun cob_3d_features profile_ne test.pcd)." << std::endl;
    return -1;
  }
  PointCloud<PointXYZ>::Ptr p (new PointCloud<PointXYZ>);
  PointCloud<Normal>::Ptr n (new PointCloud<Normal>);
  PointCloud<InterestPoint>::Ptr ip (new PointCloud<InterestPoint>);
  pcl::PointCloud<pcl::PointNormal> p_n;
  PrecisionStopWatch t;
  std::string file_ = argv[1];
  PCDReader r;
  if (r.read (file_, *p) == -1)
    return -1;

  Eigen::Vector3f normal;
  determinePlaneNormal (p, normal);
  //std::cout << normal << std::endl;

  cob_3d_features::OrganizedNormalEstimation<PointXYZ, Normal, PointLabel> ne;
  ne.setPixelSearchRadius (8, 2, 2);
  //ne.setSkipDistantPointThreshold(8);
  ne.setInputCloud (p);
  PointCloud<PointLabel>::Ptr labels (new PointCloud<PointLabel>);
  ne.setOutputLabels (labels);
  t.precisionStart ();
  ne.compute (*n);
  std::cout << t.precisionStop () << "s\t for organized normal estimation" << std::endl;

  cob_3d_features::OrganizedNormalEstimationOMP<PointXYZ, Normal, PointLabel> ne_omp;
  ne_omp.setPixelSearchRadius (8, 2, 2);
  //ne.setSkipDistantPointThreshold(8);
  ne_omp.setInputCloud (p);
  //PointCloud<PointLabel>::Ptr labels(new PointCloud<PointLabel>);
  ne_omp.setOutputLabels (labels);
  t.precisionStart ();
  ne_omp.compute (*n);
  std::cout << t.precisionStop () << "s\t for organized normal estimation (OMP)" << std::endl;
  concatenateFields (*p, *n, p_n);
  io::savePCDFileASCII ("normals_organized.pcd", p_n);

  double good_thr = 0.97;
  unsigned int ctr = 0, nan_ctr = 0;
  double d_sum = 0;
  for (unsigned int i = 0; i < p->size (); i++)
  {
    if (pcl_isnan(n->points[i].normal[0]))
    {
      nan_ctr++;
      continue;
    }
    double d = normal.dot (n->points[i].getNormalVector3fMap ());
    d_sum += fabs (1 - fabs (d));
    if (fabs (d) > good_thr)
      ctr++;
  }
  std::cout << "Average error: " << d_sum / p->size () << std::endl;
  std::cout << "Ratio of good normals: " << (double)ctr / p->size () << std::endl;
  std::cout << "Invalid normals: " << nan_ctr << std::endl;

  IntegralImageNormalEstimation<PointXYZ, Normal> ne2;
  ne2.setNormalEstimationMethod (ne2.COVARIANCE_MATRIX);
  ne2.setMaxDepthChangeFactor (0.02f);
  ne2.setNormalSmoothingSize (10.0f);
  ne2.setDepthDependentSmoothing (true);
  ne2.setInputCloud (p);
  t.precisionStart ();
  ne2.compute (*n);
  std::cout << t.precisionStop () << "s\t for integral image normal estimation" << std::endl;
  concatenateFields (*p, *n, p_n);
  io::savePCDFileASCII ("normals_integral.pcd", p_n);

  ctr = 0;
  nan_ctr = 0;
  d_sum = 0;
  for (unsigned int i = 0; i < p->size (); i++)
  {
    if (pcl_isnan(n->points[i].normal[0]))
    {
      nan_ctr++;
      continue;
    }
    double d = normal.dot (n->points[i].getNormalVector3fMap ());
    d_sum += fabs (1 - fabs (d));
    if (fabs (d) > good_thr)
      ctr++;
  }
  std::cout << "Average error: " << d_sum / p->size () << std::endl;
  std::cout << "Ratio of good normals: " << (double)ctr / p->size () << std::endl;
  std::cout << "Invalid normals: " << nan_ctr << std::endl;

  NormalEstimationOMP<PointXYZ, Normal> ne3;
  ne3.setInputCloud (p);
  ne3.setNumberOfThreads (4);
  ne3.setKSearch (256);
  //ne3.setRadiusSearch(0.01);
  t.precisionStart ();
  ne3.compute (*n);
  std::cout << t.precisionStop () << "s\t for vanilla normal estimation" << std::endl;
  concatenateFields (*p, *n, p_n);
  io::savePCDFileASCII ("normals_vanilla.pcd", p_n);

  ctr = 0;
  nan_ctr = 0;
  d_sum = 0;
  for (unsigned int i = 0; i < p->size (); i++)
  {
    if (pcl_isnan(n->points[i].normal[0]))
    {
      nan_ctr++;
      continue;
    }
    double d = normal.dot (n->points[i].getNormalVector3fMap ());
    d_sum += fabs (1 - fabs (d));
    if (fabs (d) > good_thr)
      ctr++;
  }
  std::cout << "Average error: " << d_sum / p->size () << std::endl;
  std::cout << "Ratio of good normals: " << (double)ctr / p->size () << std::endl;
  std::cout << "Invalid normals: " << nan_ctr << std::endl;

  return 0;
}