void
pcl::ihs::OfflineIntegration::computationThread ()
{
  std::vector <std::string> filenames;

  if (!this->getFilesFromDirectory (path_dir_, ".pcd", filenames))
  {
    std::cerr << "ERROR in offline_integration.cpp: Could not get the files from the directory\n";
    return;
  }

  // First cloud is reference model
  std::cerr << "Processing file " << std::setw (5) << 1 << " / " << filenames.size () << std::endl;
  CloudXYZRGBNormalPtr cloud_model (new CloudXYZRGBNormal ());
  Eigen::Matrix4f T = Eigen::Matrix4f::Identity ();
  if (!this->load (filenames [0], cloud_model, T))
  {
    std::cerr << "ERROR in offline_integration.cpp: Could not load the model cloud.\n";
    return;
  }

  pcl::transformPointCloudWithNormals (*cloud_model, *cloud_model, T);

  if (!integration_->reconstructMesh (cloud_model, mesh_model_))
  {
    std::cerr << "ERROR in offline_integration.cpp: Could not reconstruct the model mesh.\n";
    return;
  }

  Base::setPivot ("model");
  Base::addMesh (mesh_model_, "model");

  if (filenames.size () < 1)
  {
    return;
  }

  for (unsigned int i=1; i<filenames.size (); ++i)
  {
    std::cerr << "Processing file " << std::setw (5) << i+1 << " / " << filenames.size () << std::endl;

    {
      boost::mutex::scoped_lock lock (mutex_);
      if (destructor_called_) return;
    }
    boost::mutex::scoped_lock lock_quit (mutex_quit_);

    CloudXYZRGBNormalPtr cloud_data (new CloudXYZRGBNormal ());
    if (!this->load (filenames [i], cloud_data, T))
    {
      std::cerr << "ERROR in offline_integration.cpp: Could not load the data cloud.\n";
      return;
    }

    if (!integration_->merge (cloud_data, mesh_model_, T))
    {
      std::cerr << "ERROR in offline_integration.cpp: merge failed.\n";
      return;
    }

    integration_->age (mesh_model_);

    {
      lock_quit.unlock ();
      boost::mutex::scoped_lock lock (mutex_);
      if (destructor_called_) return;

      Base::addMesh (mesh_model_, "model", Eigen::Isometry3d (T.inverse ().cast <double> ()));
      Base::calcFPS (computation_fps_);
    }
  }
  Base::setPivot ("model");
}