int
main (int argc, char **argv)
{
  double dist = 2.5;
  pcl::console::parse_argument (argc, argv, "-d", dist);

  int iter = 10;
  pcl::console::parse_argument (argc, argv, "-i", iter);

  int lumIter = 1;
  pcl::console::parse_argument (argc, argv, "-l", lumIter);

  double loopDist = 5.0;
  pcl::console::parse_argument (argc, argv, "-D", loopDist);

  int loopCount = 20;
  pcl::console::parse_argument (argc, argv, "-c", loopCount);

  pcl::registration::LUM<PointType> lum;
  lum.setMaxIterations (lumIter);
  lum.setConvergenceThreshold (0.001f);

  std::vector<int> pcd_indices;
  pcd_indices = pcl::console::parse_file_extension_argument (argc, argv, ".pcd");

  CloudVector clouds;
  for (size_t i = 0; i < pcd_indices.size (); i++)
  {
    CloudPtr pc (new Cloud);
    pcl::io::loadPCDFile (argv[pcd_indices[i]], *pc);
    clouds.push_back (CloudPair (argv[pcd_indices[i]], pc));
    std::cout << "loading file: " << argv[pcd_indices[i]] << " size: " << pc->size () << std::endl;
    lum.addPointCloud (clouds[i].second);
  }

  for (int i = 0; i < iter; i++)
  {
    for (size_t i = 1; i < clouds.size (); i++)
      for (size_t j = 0; j < i; j++)
      {
        Eigen::Vector4f ci, cj;
        pcl::compute3DCentroid (*(clouds[i].second), ci);
        pcl::compute3DCentroid (*(clouds[j].second), cj);
        Eigen::Vector4f diff = ci - cj;

        //std::cout << i << " " << j << " " << diff.norm () << std::endl;

        if(diff.norm () < loopDist && (i - j == 1 || i - j > loopCount))
        {
          if(i - j > loopCount)
            std::cout << "add connection between " << i << " (" << clouds[i].first << ") and " << j << " (" << clouds[j].first << ")" << std::endl;
          pcl::registration::CorrespondenceEstimation<PointType, PointType> ce;
          ce.setInputTarget (clouds[i].second);
          ce.setInputSource (clouds[j].second);
          pcl::CorrespondencesPtr corr (new pcl::Correspondences);
          ce.determineCorrespondences (*corr, dist);
          if (corr->size () > 2)
            lum.setCorrespondences (j, i, corr);
        }
      }

    lum.compute ();

    for(size_t i = 0; i < lum.getNumVertices (); i++)
    {
      //std::cout << i << ": " << lum.getTransformation (i) (0, 3) << " " << lum.getTransformation (i) (1, 3) << " " << lum.getTransformation (i) (2, 3) << std::endl;
      clouds[i].second = lum.getTransformedCloud (i);
    }
  }

  for(size_t i = 0; i < lum.getNumVertices (); i++)
  {
    std::string result_filename (clouds[i].first);
    result_filename = result_filename.substr (result_filename.rfind ("/") + 1);
    pcl::io::savePCDFileBinary (result_filename.c_str (), *(clouds[i].second));
    //std::cout << "saving result to " << result_filename << std::endl;
  }

  return 0;
}