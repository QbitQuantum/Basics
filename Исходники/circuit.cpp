Eigen::Vector3d Circuit::GetField(const Eigen::Vector3d& point) {
  double segmentLength = 2.0*NXGR_PI*m_radius/m_segments;
  double segmentCoeff = PERMIABILITY_OVER_4PI*segmentLength*m_current;

  Eigen::Vector3d B(0.0);
  Eigen::Vector3d pos(0.0, 0.0, 0.0);
  Eigen::Vector3d up(0.0, 0.0, 1.0);

  double angle = 0.0;
  double angleInc = 2.0*NXGR_PI/m_segments;
  for(int i=0; i<m_segments; i++) {
    pos[0] = m_radius*cos(angle);
    pos[1] = m_radius*sin(angle);
    Eigen::Vector3d flow = pos.cross(up);
    flow.normalize();
    Eigen::Vector3d segmentB = GetFieldFromPoint(point, pos, flow, segmentCoeff);
    B.array() += segmentB.array();
    angle += angleInc;
  }
  return B;
}