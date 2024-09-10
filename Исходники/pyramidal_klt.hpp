template <typename PointInT, typename IntensityT> void
pcl::tracking::PyramidalKLTTracker<PointInT, IntensityT>::track (const PointCloudInConstPtr& prev_input,
                                                                 const PointCloudInConstPtr& input,
                                                                 const std::vector<FloatImageConstPtr>& prev_pyramid,
                                                                 const std::vector<FloatImageConstPtr>& pyramid,
                                                                 const pcl::PointCloud<pcl::PointUV>::ConstPtr& prev_keypoints,
                                                                 pcl::PointCloud<pcl::PointUV>::Ptr& keypoints,
                                                                 std::vector<int>& status,
                                                                 Eigen::Affine3f& motion) const
{
  std::vector<Eigen::Array2f, Eigen::aligned_allocator<Eigen::Array2f> > next_pts (prev_keypoints->size ());
  Eigen::Array2f half_win ((track_width_-1)*0.5f, (track_height_-1)*0.5f);
  pcl::TransformationFromCorrespondences transformation_computer;
  const int nb_points = prev_keypoints->size ();
  for (int level = nb_levels_ - 1; level >= 0; --level)
  {
    const FloatImage& prev = *(prev_pyramid[level*3]);
    const FloatImage& next = *(pyramid[level*3]);
    const FloatImage& grad_x = *(prev_pyramid[level*3+1]);
    const FloatImage& grad_y = *(prev_pyramid[level*3+2]);

    Eigen::ArrayXXf prev_win (track_height_, track_width_);
    Eigen::ArrayXXf grad_x_win (track_height_, track_width_);
    Eigen::ArrayXXf grad_y_win (track_height_, track_width_);
    float ratio (1./(1 << level));
    for (int ptidx = 0; ptidx < nb_points; ptidx++)
    {
      Eigen::Array2f prev_pt (prev_keypoints->points[ptidx].u * ratio,
                              prev_keypoints->points[ptidx].v * ratio);
      Eigen::Array2f next_pt;
      if (level == nb_levels_ -1)
        next_pt = prev_pt;
      else
        next_pt = next_pts[ptidx]*2.f;

      next_pts[ptidx] = next_pt;

      Eigen::Array2i iprev_point;
      prev_pt -= half_win;
      iprev_point[0] = floor (prev_pt[0]);
      iprev_point[1] = floor (prev_pt[1]);

      if (iprev_point[0] < -track_width_ || (uint32_t) iprev_point[0] >= grad_x.width ||
          iprev_point[1] < -track_height_ || (uint32_t) iprev_point[1] >= grad_y.height)
      {
        if (level == 0)
          status [ptidx] = -1;
        continue;
      }

      float a = prev_pt[0] - iprev_point[0];
      float b = prev_pt[1] - iprev_point[1];
      Eigen::Array4f weight;
      weight[0] = (1.f - a)*(1.f - b);
      weight[1] = a*(1.f - b);
      weight[2] = (1.f - a)*b;
      weight[3] = 1 - weight[0] - weight[1] - weight[2];

      Eigen::Array3f covar = Eigen::Array3f::Zero ();
      spatialGradient (prev, grad_x, grad_y, iprev_point, weight, prev_win, grad_x_win, grad_y_win, covar);

      float det = covar[0]*covar[2] - covar[1]*covar[1];
      float min_eigenvalue = (covar[2] + covar[0] - std::sqrt ((covar[0]-covar[2])*(covar[0]-covar[2]) + 4.f*covar[1]*covar[1]))/2.f;

      if (min_eigenvalue < min_eigenvalue_threshold_ || det < std::numeric_limits<float>::epsilon ())
      {
        status[ptidx] = -2;
        continue;
      }

      det = 1.f/det;
      next_pt -= half_win;

      Eigen::Array2f prev_delta (0, 0);
      for (unsigned int j = 0; j < max_iterations_; j++)
      {
        Eigen::Array2i inext_pt = next_pt.floor ().cast<int> ();

        if (inext_pt[0] < -track_width_ || (uint32_t) inext_pt[0] >= next.width ||
            inext_pt[1] < -track_height_ || (uint32_t) inext_pt[1] >= next.height)
        {
          if (level == 0)
            status[ptidx] = -1;
          break;
        }

        a = next_pt[0] - inext_pt[0];
        b = next_pt[1] - inext_pt[1];
        weight[0] = (1.f - a)*(1.f - b);
        weight[1] = a*(1.f - b);
        weight[2] = (1.f - a)*b;
        weight[3] = 1 - weight[0] - weight[1] - weight[2];
        // compute mismatch vector
        Eigen::Array2f beta = Eigen::Array2f::Zero ();
        mismatchVector (prev_win, grad_x_win, grad_y_win, next, inext_pt, weight, beta);
        // optical flow resolution
        Eigen::Vector2f delta ((covar[1]*beta[1] - covar[2]*beta[0])*det, (covar[1]*beta[0] - covar[0]*beta[1])*det);
        // update position
        next_pt[0] += delta[0]; next_pt[1] += delta[1];
        next_pts[ptidx] = next_pt + half_win;

        if (delta.squaredNorm () <= epsilon_)
          break;

        if (j > 0 && std::abs (delta[0] + prev_delta[0]) < 0.01 &&
            std::abs (delta[1] + prev_delta[1]) < 0.01 )
        {
          next_pts[ptidx][0] -= delta[0]*0.5f;
          next_pts[ptidx][1] -= delta[1]*0.5f;
          break;
        }
        // update delta
        prev_delta = delta;
      }

      // update tracked points
      if (level == 0 && !status[ptidx])
      {
        Eigen::Array2f next_point = next_pts[ptidx] - half_win;
        Eigen::Array2i inext_point;

        inext_point[0] = floor (next_point[0]);
        inext_point[1] = floor (next_point[1]);

        if (inext_point[0] < -track_width_ || (uint32_t) inext_point[0] >= next.width ||
            inext_point[1] < -track_height_ || (uint32_t) inext_point[1] >= next.height)
        {
          status[ptidx] = -1;
          continue;
        }
        // insert valid keypoint
        pcl::PointUV n;
        n.u = next_pts[ptidx][0];
        n.v = next_pts[ptidx][1];
        keypoints->push_back (n);
        // add points pair to compute transformation
        inext_point[0] = floor (next_pts[ptidx][0]);
        inext_point[1] = floor (next_pts[ptidx][1]);
        iprev_point[0] = floor (prev_keypoints->points[ptidx].u);
        iprev_point[1] = floor (prev_keypoints->points[ptidx].v);
        const PointInT& prev_pt = prev_input->points[iprev_point[1]*prev_input->width + iprev_point[0]];
        const PointInT& next_pt = input->points[inext_point[1]*input->width + inext_point[0]];
        transformation_computer.add (prev_pt.getVector3fMap (), next_pt.getVector3fMap (), 1.0);
      }
    }
  }
  motion = transformation_computer.getTransformation ();
}