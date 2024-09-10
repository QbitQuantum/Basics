template <typename PointNT> void
pcl::GridProjection<PointNT>::findIntersection (int level,
                                                const std::vector<Eigen::Vector4f, Eigen::aligned_allocator<Eigen::Vector4f> > &end_pts,
                                                const std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > &vect_at_end_pts,
                                                const Eigen::Vector4f &start_pt,
                                                std::vector <int> &pt_union_indices,
                                                Eigen::Vector4f &intersection)
{
  assert (end_pts.size () == 2);
  assert (vect_at_end_pts.size () == 2);

  Eigen::Vector3f vec;
  getVectorAtPoint (start_pt, pt_union_indices, vec);
  double d1 = getD1AtPoint (start_pt, vec, pt_union_indices);
  std::vector<Eigen::Vector4f, Eigen::aligned_allocator<Eigen::Vector4f> > new_end_pts (2);
  std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > new_vect_at_end_pts (2);
  if ((fabs (d1) < 10e-3) || (level == max_binary_search_level_))
  {
    intersection = start_pt;
    return;
  }
  else
  {
    vec.normalize ();
    if (vec.dot (vect_at_end_pts[0]) < 0)
    {
      Eigen::Vector4f new_start_pt = end_pts[0] + (start_pt - end_pts[0]) * 0.5;
      new_end_pts[0] = end_pts[0];
      new_end_pts[1] = start_pt;
      new_vect_at_end_pts[0] = vect_at_end_pts[0];
      new_vect_at_end_pts[1] = vec;
      findIntersection (level + 1, new_end_pts, new_vect_at_end_pts, new_start_pt, pt_union_indices, intersection);
      return;
    }
    if (vec.dot (vect_at_end_pts[1]) < 0)
    {
      Eigen::Vector4f new_start_pt = start_pt + (end_pts[1] - start_pt) * 0.5;
      new_end_pts[0] = start_pt;
      new_end_pts[1] = end_pts[1];
      new_vect_at_end_pts[0] = vec;
      new_vect_at_end_pts[1] = vect_at_end_pts[1];
      findIntersection (level + 1, new_end_pts, new_vect_at_end_pts, new_start_pt, pt_union_indices, intersection);
      return;
    }
    intersection = start_pt;
    return;
  }
}