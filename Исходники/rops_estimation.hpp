template <typename PointInT, typename PointOutT> void
pcl::ROPSEstimation <PointInT, PointOutT>::computeLRF (const PointInT& point, const std::set <unsigned int>& local_triangles, Eigen::Matrix3f& lrf_matrix) const
{
  const unsigned int number_of_triangles = static_cast <unsigned int> (local_triangles.size ());

  std::vector<Eigen::Matrix3f, Eigen::aligned_allocator<Eigen::Matrix3f> > scatter_matrices (number_of_triangles);
  std::vector <float> triangle_area (number_of_triangles);
  std::vector <float> distance_weight (number_of_triangles);

  float total_area = 0.0f;
  const float coeff = 1.0f / 12.0f;
  const float coeff_1_div_3 = 1.0f / 3.0f;

  Eigen::Vector3f feature_point (point.x, point.y, point.z);

  std::set <unsigned int>::const_iterator it;
  unsigned int i_triangle = 0;
  for (it = local_triangles.begin (), i_triangle = 0; it != local_triangles.end (); it++, i_triangle++)
  {
    Eigen::Vector3f pt[3];
    for (unsigned int i_vertex = 0; i_vertex < 3; i_vertex++)
    {
      const unsigned int index = triangles_[*it].vertices[i_vertex];
      pt[i_vertex] (0) = surface_->points[index].x;
      pt[i_vertex] (1) = surface_->points[index].y;
      pt[i_vertex] (2) = surface_->points[index].z;
    }

    const float curr_area = ((pt[1] - pt[0]).cross (pt[2] - pt[0])).norm ();
    triangle_area[i_triangle] = curr_area;
    total_area += curr_area;

    distance_weight[i_triangle] = pow (support_radius_ - (feature_point - (pt[0] + pt[1] + pt[2]) * coeff_1_div_3).norm (), 2.0f);

    Eigen::Matrix3f curr_scatter_matrix;
    curr_scatter_matrix.setZero ();
    for (unsigned int i_pt = 0; i_pt < 3; i_pt++)
    {
      Eigen::Vector3f vec = pt[i_pt] - feature_point;
      curr_scatter_matrix += vec * (vec.transpose ());
      for (unsigned int j_pt = 0; j_pt < 3; j_pt++)
        curr_scatter_matrix += vec * ((pt[j_pt] - feature_point).transpose ());
    }
    scatter_matrices[i_triangle] = coeff * curr_scatter_matrix;
  }

  if (std::abs (total_area) < std::numeric_limits <float>::epsilon ())
    total_area = 1.0f / total_area;
  else
    total_area = 1.0f;

  Eigen::Matrix3f overall_scatter_matrix;
  overall_scatter_matrix.setZero ();
  std::vector<float> total_weight (number_of_triangles);
  const float denominator = 1.0f / 6.0f;
  for (unsigned int i_triangle = 0; i_triangle < number_of_triangles; i_triangle++)
  {
    float factor = distance_weight[i_triangle] * triangle_area[i_triangle] * total_area;
    overall_scatter_matrix += factor * scatter_matrices[i_triangle];
    total_weight[i_triangle] = factor * denominator;
  }

  Eigen::Vector3f v1, v2, v3;
  computeEigenVectors (overall_scatter_matrix, v1, v2, v3);

  float h1 = 0.0f;
  float h3 = 0.0f;
  for (it = local_triangles.begin (), i_triangle = 0; it != local_triangles.end (); it++, i_triangle++)
  {
    Eigen::Vector3f pt[3];
    for (unsigned int i_vertex = 0; i_vertex < 3; i_vertex++)
    {
      const unsigned int index = triangles_[*it].vertices[i_vertex];
      pt[i_vertex] (0) = surface_->points[index].x;
      pt[i_vertex] (1) = surface_->points[index].y;
      pt[i_vertex] (2) = surface_->points[index].z;
    }

    float factor1 = 0.0f;
    float factor3 = 0.0f;
    for (unsigned int i_pt = 0; i_pt < 3; i_pt++)
    {
      Eigen::Vector3f vec = pt[i_pt] - feature_point;
      factor1 += vec.dot (v1);
      factor3 += vec.dot (v3);
    }
    h1 += total_weight[i_triangle] * factor1;
    h3 += total_weight[i_triangle] * factor3;
  }

  if (h1 < 0.0f) v1 = -v1;
  if (h3 < 0.0f) v3 = -v3;

  v2 = v3.cross (v1);

  lrf_matrix.row (0) = v1;
  lrf_matrix.row (1) = v2;
  lrf_matrix.row (2) = v3;
}