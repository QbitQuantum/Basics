void
pcl::CRHEstimation<PointInT, PointNT, PointOutT>::computeFeature (PointCloudOut &output)
{
  // Check if input was set
  if (!normals_)
  {
    PCL_ERROR ("[pcl::%s::computeFeature] No input dataset containing normals was given!\n", getClassName ().c_str ());
    output.width = output.height = 0;
    output.points.clear ();
    return;
  }

  if (normals_->points.size () != surface_->points.size ())
  {
    PCL_ERROR ("[pcl::%s::computeFeature] The number of points in the input dataset differs from the number of points in the dataset containing the normals!\n", getClassName ().c_str ());
    output.width = output.height = 0;
    output.points.clear ();
    return;
  }

  Eigen::Vector3f plane_normal;
  plane_normal[0] = -centroid_[0];
  plane_normal[1] = -centroid_[1];
  plane_normal[2] = -centroid_[2];
  Eigen::Vector3f z_vector = Eigen::Vector3f::UnitZ ();
  plane_normal.normalize ();
  Eigen::Vector3f axis = plane_normal.cross (z_vector);
  double rotation = -asin (axis.norm ());
  axis.normalize ();

  int nbins = nbins_;
  int bin_angle = 360 / nbins;

  Eigen::Affine3f transformPC (Eigen::AngleAxisf (static_cast<float> (rotation), axis));

  pcl::PointCloud<pcl::PointNormal> grid;
  grid.points.resize (indices_->size ());

  for (size_t i = 0; i < indices_->size (); i++)
  {
    grid.points[i].getVector4fMap () = surface_->points[(*indices_)[i]].getVector4fMap ();
    grid.points[i].getNormalVector4fMap () = normals_->points[(*indices_)[i]].getNormalVector4fMap ();
  }

  pcl::transformPointCloudWithNormals (grid, grid, transformPC);

  //fill spatial data vector and the zero-initialize or "value-initialize" an array on c++, 
  // the initialization is made with () after the [nbins]
  kiss_fft_scalar * spatial_data = new kiss_fft_scalar[nbins]();
  

  float sum_w = 0, w = 0;
  int bin = 0;
  for (const auto &point : grid.points)
  {
    bin = static_cast<int> ((((atan2 (point.normal_y, point.normal_x) + M_PI) * 180 / M_PI) / bin_angle)) % nbins;
    w = std::sqrt (point.normal_y * point.normal_y + point.normal_x * point.normal_x);
    sum_w += w;
    spatial_data[bin] += w;
  }

  for (int i = 0; i < nbins; ++i)
    spatial_data[i] /= sum_w;

  kiss_fft_cpx * freq_data = new kiss_fft_cpx[nbins / 2 + 1];
  kiss_fftr_cfg mycfg = kiss_fftr_alloc (nbins, 0, NULL, NULL);
  kiss_fftr (mycfg, spatial_data, freq_data);

  output.points.resize (1);
  output.width = output.height = 1;

  output.points[0].histogram[0] = freq_data[0].r / freq_data[0].r; //dc
  int k = 1;
  for (int i = 1; i < (nbins / 2); i++, k += 2)
  {
    output.points[0].histogram[k] = freq_data[i].r / freq_data[0].r;
    output.points[0].histogram[k + 1] = freq_data[i].i / freq_data[0].r;
  }

  output.points[0].histogram[nbins - 1] = freq_data[nbins / 2].r / freq_data[0].r; //nyquist

  delete[] spatial_data;
  delete[] freq_data;

}