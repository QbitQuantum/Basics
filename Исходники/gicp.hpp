template <typename PointSource, typename PointTarget> inline void
pcl::GeneralizedIterativeClosestPoint<PointSource, PointTarget>::computeTransformation (PointCloudSource &output, const Eigen::Matrix4f& guess)
{
  pcl::IterativeClosestPoint<PointSource, PointTarget>::initComputeReciprocal ();
  using namespace std;
  // Difference between consecutive transforms
  double delta = 0;
  // Get the size of the target
  const size_t N = indices_->size ();
  // Set the mahalanobis matrices to identity
  mahalanobis_.resize (N, Eigen::Matrix3d::Identity ());
  // Compute target cloud covariance matrices
  if (target_covariances_.empty ())
    computeCovariances<PointTarget> (target_, tree_, target_covariances_);
  // Compute input cloud covariance matrices
  if (input_covariances_.empty ())
    computeCovariances<PointSource> (input_, tree_reciprocal_, input_covariances_);

  base_transformation_ = guess;
  nr_iterations_ = 0;
  converged_ = false;
  double dist_threshold = corr_dist_threshold_ * corr_dist_threshold_;
  std::vector<int> nn_indices (1);
  std::vector<float> nn_dists (1);

  while(!converged_)
  {
    size_t cnt = 0;
    std::vector<int> source_indices (indices_->size ());
    std::vector<int> target_indices (indices_->size ());

    // guess corresponds to base_t and transformation_ to t
    Eigen::Matrix4d transform_R = Eigen::Matrix4d::Zero ();
    for(size_t i = 0; i < 4; i++)
      for(size_t j = 0; j < 4; j++)
        for(size_t k = 0; k < 4; k++)
          transform_R(i,j)+= double(transformation_(i,k)) * double(guess(k,j));

    Eigen::Matrix3d R = transform_R.topLeftCorner<3,3> ();

    for (size_t i = 0; i < N; i++)
    {
      PointSource query = output[i];
      query.getVector4fMap () = guess * query.getVector4fMap ();
      query.getVector4fMap () = transformation_ * query.getVector4fMap ();

      if (!searchForNeighbors (query, nn_indices, nn_dists))
      {
        PCL_ERROR ("[pcl::%s::computeTransformation] Unable to find a nearest neighbor in the target dataset for point %d in the source!\n", getClassName ().c_str (), (*indices_)[i]);
        return;
      }
      
      // Check if the distance to the nearest neighbor is smaller than the user imposed threshold
      if (nn_dists[0] < dist_threshold)
      {
        Eigen::Matrix3d &C1 = input_covariances_[i];
        Eigen::Matrix3d &C2 = target_covariances_[nn_indices[0]];
        Eigen::Matrix3d &M = mahalanobis_[i];
        // M = R*C1
        M = R * C1;
        // temp = M*R' + C2 = R*C1*R' + C2
        Eigen::Matrix3d temp = M * R.transpose();        
        temp+= C2;
        // M = temp^-1
        M = temp.inverse ();
        source_indices[cnt] = static_cast<int> (i);
        target_indices[cnt] = nn_indices[0];
        cnt++;
      }
    }
    // Resize to the actual number of valid correspondences
    source_indices.resize(cnt); target_indices.resize(cnt);
    /* optimize transformation using the current assignment and Mahalanobis metrics*/
    previous_transformation_ = transformation_;
    //optimization right here
    try
    {
      rigid_transformation_estimation_(output, source_indices, *target_, target_indices, transformation_);
      /* compute the delta from this iteration */
      delta = 0.;
      for(int k = 0; k < 4; k++) {
        for(int l = 0; l < 4; l++) {
          double ratio = 1;
          if(k < 3 && l < 3) // rotation part of the transform
            ratio = 1./rotation_epsilon_;
          else
            ratio = 1./transformation_epsilon_;
          double c_delta = ratio*fabs(previous_transformation_(k,l) - transformation_(k,l));
          if(c_delta > delta)
            delta = c_delta;
        }
      }
    } 
    catch (PCLException &e)
    {
      PCL_DEBUG ("[pcl::%s::computeTransformation] Optimization issue %s\n", getClassName ().c_str (), e.what ());
      break;
    }
    nr_iterations_++;
    // Check for convergence
    if (nr_iterations_ >= max_iterations_ || delta < 1)
    {
      converged_ = true;
      previous_transformation_ = transformation_;
      PCL_DEBUG ("[pcl::%s::computeTransformation] Convergence reached. Number of iterations: %d out of %d. Transformation difference: %f\n",
                 getClassName ().c_str (), nr_iterations_, max_iterations_, (transformation_ - previous_transformation_).array ().abs ().sum ());
    } 
    else
      PCL_DEBUG ("[pcl::%s::computeTransformation] Convergence failed\n", getClassName ().c_str ());
  }
  //for some reason the static equivalent methode raises an error
  // final_transformation_.block<3,3> (0,0) = (transformation_.block<3,3> (0,0)) * (guess.block<3,3> (0,0));
  // final_transformation_.block <3, 1> (0, 3) = transformation_.block <3, 1> (0, 3) + guess.rightCols<1>.block <3, 1> (0, 3);
  final_transformation_.topLeftCorner (3,3) = previous_transformation_.topLeftCorner (3,3) * guess.topLeftCorner (3,3);
  final_transformation_(0,3) = previous_transformation_(0,3) + guess(0,3);
  final_transformation_(1,3) = previous_transformation_(1,3) + guess(1,3);
  final_transformation_(2,3) = previous_transformation_(2,3) + guess(2,3);
}