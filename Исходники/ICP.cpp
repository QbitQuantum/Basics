bool
pcl::ihs::ICP::findTransformation (const CloudModelConstPtr&     cloud_model,
                                   const CloudProcessedConstPtr& cloud_data,
                                   const Transformation&         T_init,
                                   Transformation&               T_final)
{
  // Check the input
  // TODO: Double check the minimum number of points necessary for icp
  const size_t n_min = 4;

  if(cloud_model->size () < n_min || cloud_data->size () < n_min)
  {
    std::cerr << "ERROR in icp.cpp: Not enough input points!\n";
    return (false);
  }

  // Convergence and registration failure
  float current_fitness  = 0.f;
  float previous_fitness = std::numeric_limits <float>::max ();
  float delta_fitness    = std::numeric_limits <float>::max ();
  float overlap          = std::numeric_limits <float>::quiet_NaN ();

  // Outlier rejection
  float squared_distance_threshold = std::numeric_limits<float>::max();

  // Transformation
  Transformation T_cur = T_init;

  // Point selection
  const CloudNormalConstPtr cloud_model_selected = this->selectModelPoints (cloud_model, T_init.inverse ());
  const CloudNormalConstPtr cloud_data_selected = this->selectDataPoints (cloud_data);

  const size_t n_data  = cloud_data_selected->size ();
  const size_t n_model = cloud_model_selected->size ();
  if(n_model < n_min || n_data < n_min)
  {
    std::cerr << "ERROR in icp.cpp: Not enough points after selection!\n";
    return (false);
  }

  // Build a kd-tree
  kd_tree_->setInputCloud (cloud_model_selected);

  // ICP main loop
  unsigned int iter = 1;
  while (true)
  {
    // Clouds with one to one correspondences
    CloudNormalPtr cloud_model_corr (new CloudNormal ());
    CloudNormalPtr cloud_data_corr (new CloudNormal ());

    cloud_model_corr->reserve (n_data);
    cloud_data_corr->reserve (n_data);

    // Accumulated error
    float squared_distance_sum = 0.f;

    // NN search
    std::vector <int>   index (1);
    std::vector <float> squared_distance (1);

    CloudNormal::const_iterator it_d = cloud_data_selected->begin ();
    for (; it_d!=cloud_data_selected->end (); ++it_d)
    {
      // Transform the data point
      PointNormal pt_d = *it_d;
      pt_d.getVector4fMap ()       = T_cur * pt_d.getVector4fMap ();
      pt_d.getNormalVector4fMap () = T_cur * pt_d.getNormalVector4fMap ();

      // Find the correspondence to the model points
      if (!kd_tree_->nearestKSearch (pt_d, 1, index, squared_distance))
      {
        std::cerr << "ERROR in icp.cpp: nearestKSearch failed!\n";
        return (false);
      }

      // Check the distance threshold
      if (squared_distance[0] < squared_distance_threshold)
      {
        if (index[0] >= cloud_model_selected->size ())
        {
          std::cerr << "ERROR in icp.cpp: Segfault!\n";
          std::cerr << "  Trying to access index " << index[0] << " >= " << cloud_model_selected->size () << std::endl;
          exit (EXIT_FAILURE);
        }

        const PointNormal& pt_m = cloud_model_selected->operator [] (index[0]);

        // Check the normals threshold
        if (pt_m.getNormalVector4fMap ().dot (pt_d.getNormalVector4fMap ()) > normals_threshold_)
        {
          squared_distance_sum += squared_distance[0];

          cloud_model_corr->push_back (pt_m);
          cloud_data_corr->push_back (pt_d);
        }
      }
    }

    // Shrink to fit ("Scott Meyers swap trick")
    CloudNormal (*cloud_model_corr).swap (*cloud_model_corr);
    CloudNormal (*cloud_data_corr).swap (*cloud_data_corr);

    const size_t n_corr = cloud_data_corr->size ();
    if (n_corr < n_min)
    {
      std::cerr << "ERROR in icp.cpp: Not enough correspondences: " << n_corr << " < " << n_min << std::endl;
      return (false);
    }

    // NOTE: The fitness is calculated with the transformation from the previous iteration (I don't re-calculate it after the transformation estimation). This means that the actual fitness will be one iteration "better" than the calculated fitness suggests. This should be no problem because the difference is small at the state of convergence.
    previous_fitness           = current_fitness;
    current_fitness            = squared_distance_sum / static_cast <float> (n_corr);
    delta_fitness              = std::abs (previous_fitness - current_fitness);
    squared_distance_threshold = squared_distance_threshold_factor_ * current_fitness;
    overlap                    = static_cast <float> (n_corr) / static_cast <float> (n_data);

    //    std::cerr << "Iter: " << std::left << std::setw(3) << iter
    //              << " | Overlap: " << std::setprecision(2) << std::setw(4) << overlap
    //              << " | current fitness: " << std::setprecision(5) << std::setw(10) << current_fitness
    //              << " | delta fitness: " << std::setprecision(5) << std::setw(10) << delta_fitness << std::endl;

    // Minimize the point to plane distance
    Transformation T_delta = Transformation::Identity ();
    if (!this->minimizePointPlane (cloud_data_corr, cloud_model_corr, T_delta))
    {
      std::cerr << "ERROR in icp.cpp: minimizePointPlane failed!\n";
      return (false);
    }

    T_cur = T_delta * T_cur;

    // Convergence
    if (delta_fitness < epsilon_) break;
    ++iter;
    if (iter > max_iterations_)   break;

  } // End ICP main loop

  // Some output
  std::cerr << "\nRegistration:\n"
            << "  - delta fitness / epsilon    : " << delta_fitness   << " / " << epsilon_
            << (delta_fitness   < epsilon_        ? " <-- :-)\n" : "\n")
            << "  - fitness       / max fitness: " << current_fitness << " / " << max_fitness_
            << (current_fitness > max_fitness_    ? " <-- :-(\n" : "\n")
            << "  - iter          / max iter   : " << iter            << " / " << max_iterations_
            << (iter            > max_iterations_ ? " <-- :-(\n" : "\n")
            << "  - overlap       / min overlap: " << overlap         << " / " << min_overlap_
            << (overlap         < min_overlap_    ? " <-- :-(\n" : "\n\n");

  if (iter > max_iterations_ || overlap <  min_overlap_ || current_fitness > max_fitness_)
  {
    return (false);
  }
  else if (delta_fitness <=epsilon_)
  {
    T_final = T_cur;
    return (true);
  }
  else
  {
    std::cerr << "ERROR in icp.cpp: Congratulations! you found a bug.\n";
    exit (EXIT_FAILURE);
  }
}