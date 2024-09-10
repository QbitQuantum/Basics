Conic UnmapConic( const Conic& c, const AbstractCamera& cam )
{
  std::vector<Eigen::Vector2d > d;
  std::vector<Eigen::Vector2d > u;

  d.push_back(c.center);
  d.push_back(Eigen::Vector2d(c.bbox.x1,c.bbox.y1));
  d.push_back(Eigen::Vector2d(c.bbox.x1,c.bbox.y2));
  d.push_back(Eigen::Vector2d(c.bbox.x2,c.bbox.y1));
  d.push_back(Eigen::Vector2d(c.bbox.x2,c.bbox.y2));

  for( int i=0; i<5; ++i )
    u.push_back( cam.unmap(d[i]) );

  // Distortion locally estimated by homography
  const Matrix3d H_du = EstimateH_ba(u,d);

  Conic ret;
//  ret.bbox = c.bbox;
  ret.C = H_du.transpose() * c.C * H_du;
  ret.Dual = ret.C.inverse();
  ret.center = u[0];
  return ret;
}