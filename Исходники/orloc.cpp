// transform distances measured with laser into points in Cartesian space
HybNav::Scan HybNav::getPoints(const HybNav::SPosition pos, const LaserProxy &laser) {
  double angle = laser.GetMinAngle();
  double resolution = laser.GetScanRes();
  double ppy = 0.04365; //TODO: this should be read from player laser.GetPose().py
  //ppy = 0;

  player_point_2d_t s;
  HybNav::Scan scan;
  for(int i=0;i<laser.GetCount();i++) {
    s.px = pos.x + cos(pos.yaw)*ppy + laser.GetRange(i) * cos(pos.yaw+angle);
    s.py = pos.y + sin(pos.yaw)*ppy + laser.GetRange(i) * sin(pos.yaw+angle);
    #if 0
    s.px = pos.x + cos(pos.yaw) * ppy + laser.GetRange(i) * cos(/*laser.GetBearing(i)*/angle + pos.yaw);
    s.py = pos.y + sin(pos.yaw) * ppy + laser.GetRange(i) * sin(/*laser.GetBearing(i)*/angle + pos.yaw);
    #endif
    scan.push_back(s);
    angle += resolution;
  }
  return scan;
}