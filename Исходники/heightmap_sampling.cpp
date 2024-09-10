bool HeightmapSampling::calculateNormalsFromHullSurface()
{
  normals_.points.clear();
  shared_ptr < PointCloud<PointXYZ> > sp;
  sp.reset(new PointCloud<PointXYZ> ());
  Vector3d search_point_center(0, 0, 0);
  vector < Vector3d > normals_prestep;

  for (unsigned int i = 0; i < convex_hull_vertices_.size(); i++)
  {
    PointXYZ p(0, 0, 0);

    for (unsigned int j = 0; j < convex_hull_vertices_[i].vertices.size(); j++)
    {
      unsigned int index = convex_hull_vertices_[i].vertices[j];

      p.x += convex_hull_points_->points[index].x;
      p.y += convex_hull_points_->points[index].y;
      p.z += convex_hull_points_->points[index].z;

    }

    p.x /= convex_hull_vertices_[i].vertices.size();
    p.y /= convex_hull_vertices_[i].vertices.size();
    p.z /= convex_hull_vertices_[i].vertices.size();

    search_point_center += Vector3d(p.x, p.y, p.z);

    sp->push_back(p);

    /* normal */
    Vector3d p_centr(p.x, p.y, p.z);

    const PointXYZ& p_a = convex_hull_points_-> points[convex_hull_vertices_[i].vertices[0]];
    const PointXYZ& p_b = convex_hull_points_-> points[convex_hull_vertices_[i].vertices[1]];
    const PointXYZ& p_c = convex_hull_points_-> points[convex_hull_vertices_[i].vertices[2]];

    Vector3d va(p_b.x - p_a.x, p_b.y - p_a.y, p_b.z - p_a.z);
    Vector3d vb(p_c.x - p_a.x, p_c.y - p_a.y, p_c.z - p_a.z);
    Vector3d vn = va.cross(vb);

    vn.normalize();

    normals_prestep.push_back(vn);

  }

  search_point_center /= sp->points.size();

  /* flip normals away from center */
  vector<bool> backside;
  backside.resize(normals_prestep.size(), false);
  for (unsigned int i = 0; i < normals_prestep.size(); i++)
  {
    Vector3d s_point(sp->points[i].x - search_point_center.x(), sp->points[i].y - search_point_center.y(),
                     sp->points[i].z - search_point_center.z());

    if (s_point.dot(normals_prestep[i]) < 0)
    {
      normals_prestep[i] = -normals_prestep[i];
    }

    Vector3d vec_vs(sp->points[i].x - viewp_trans_.x(), sp->points[i].y - viewp_trans_.y(),
        sp->points[i].z - viewp_trans_.z());
    vec_vs.normalize();

    if (vec_vs.dot(normals_prestep[i]) > 0)
    {
      backside[i] = true;
    }
  }

  /* set normals */
  for (unsigned int i = 0; i < normals_prestep.size(); i++)
  {
    if (backside[i])
    {
      continue;
    }

    Normal pcl_n;
    pcl_n.normal_x = normals_prestep[i].x();
    pcl_n.normal_y = normals_prestep[i].y();
    pcl_n.normal_z = normals_prestep[i].z();
    normals_.push_back(pcl_n);
  }

  /* filter and set search-points */
  for (int i = backside.size() - 1; i >= 0; i--)
  {
    if (backside[i])
    {
      sp->points.erase(sp->points.begin() + i);
    }
  }
  search_points_ = sp;

  ROS_DEBUG_STREAM("grasp_template::HeightmapSampling: #normals: " << normals_.size()
      << ", #search_points: " << search_points_->points.size() << endl);
  return true;
}