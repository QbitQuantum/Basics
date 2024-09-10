TEST (PCL, BoundaryEstimation)
{
  Eigen::Vector4f u = Eigen::Vector4f::Zero ();
  Eigen::Vector4f v = Eigen::Vector4f::Zero ();

  // Estimate normals first
  NormalEstimation<PointXYZ, Normal> n;
  PointCloud<Normal>::Ptr normals (new PointCloud<Normal> ());
  // set parameters
  n.setInputCloud (cloud.makeShared ());
  boost::shared_ptr<vector<int> > indicesptr (new vector<int> (indices));
  n.setIndices (indicesptr);
  n.setSearchMethod (tree);
  n.setKSearch (static_cast<int> (indices.size ()));
  // estimate
  n.compute (*normals);

  BoundaryEstimation<PointXYZ, Normal, Boundary> b;
  b.setInputNormals (normals);
  EXPECT_EQ (b.getInputNormals (), normals);

  // getCoordinateSystemOnPlane
  for (size_t i = 0; i < normals->points.size (); ++i)
  {
    b.getCoordinateSystemOnPlane (normals->points[i], u, v);
    Vector4fMap n4uv = normals->points[i].getNormalVector4fMap ();
    EXPECT_NEAR (n4uv.dot(u), 0, 1e-4);
    EXPECT_NEAR (n4uv.dot(v), 0, 1e-4);
    EXPECT_NEAR (u.dot(v), 0, 1e-4);
  }

  // isBoundaryPoint (indices)
  bool pt = false;
  pt = b.isBoundaryPoint (cloud, 0, indices, u, v, float (M_PI) / 2.0);
  EXPECT_EQ (pt, false);
  pt = b.isBoundaryPoint (cloud, static_cast<int> (indices.size ()) / 3, indices, u, v, float (M_PI) / 2.0);
  EXPECT_EQ (pt, false);
  pt = b.isBoundaryPoint (cloud, static_cast<int> (indices.size ()) / 2, indices, u, v, float (M_PI) / 2.0);
  EXPECT_EQ (pt, false);
  pt = b.isBoundaryPoint (cloud, static_cast<int> (indices.size ()) - 1, indices, u, v, float (M_PI) / 2.0);
  EXPECT_EQ (pt, true);

  // isBoundaryPoint (points)
  pt = false;
  pt = b.isBoundaryPoint (cloud, cloud.points[0], indices, u, v, float (M_PI) / 2.0);
  EXPECT_EQ (pt, false);
  pt = b.isBoundaryPoint (cloud, cloud.points[indices.size () / 3], indices, u, v, float (M_PI) / 2.0);
  EXPECT_EQ (pt, false);
  pt = b.isBoundaryPoint (cloud, cloud.points[indices.size () / 2], indices, u, v, float (M_PI) / 2.0);
  EXPECT_EQ (pt, false);
  pt = b.isBoundaryPoint (cloud, cloud.points[indices.size () - 1], indices, u, v, float (M_PI) / 2.0);
  EXPECT_EQ (pt, true);

  // Object
  PointCloud<Boundary>::Ptr bps (new PointCloud<Boundary> ());

  // set parameters
  b.setInputCloud (cloud.makeShared ());
  b.setIndices (indicesptr);
  b.setSearchMethod (tree);
  b.setKSearch (static_cast<int> (indices.size ()));

  // estimate
  b.compute (*bps);
  EXPECT_EQ (bps->points.size (), indices.size ());

  pt = bps->points[0].boundary_point;
  EXPECT_EQ (pt, false);
  pt = bps->points[indices.size () / 3].boundary_point;
  EXPECT_EQ (pt, false);
  pt = bps->points[indices.size () / 2].boundary_point;
  EXPECT_EQ (pt, false);
  pt = bps->points[indices.size () - 1].boundary_point;
  EXPECT_EQ (pt, true);
}