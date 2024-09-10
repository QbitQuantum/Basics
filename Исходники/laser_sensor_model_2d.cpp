  void
  LaserSensorModel2D::setInformationForVertexPoint(EdgeSE2PointXYCov*& edge, VertexPointXYCov*& point, LaserSensorParams& params)
  {
    double beamAngle = atan2(edge->measurement()(1), edge->measurement()(0));
    ///calculate incidence angle in point frame
    Eigen::Vector2d beam = edge->measurement();

    Eigen::Vector2d normal = point->normal();
    beam = beam.normalized();
    normal = normal.normalized();
    double incidenceAngle = 0.0;
    if(point->covariance() != Eigen::Matrix2d::Identity())
      incidenceAngle = acos(normal.dot(beam));

    double d = (tan(params.angularResolution * 0.5) * edge->measurement().norm());
    ///uncertainty of the surface measurement in direction of the beam
    double dk = fabs(params.scale * (d / cos(incidenceAngle)));
    edge->information().setIdentity();
    edge->information()(0,0) = 1.0 / ((dk + params.sensorPrecision) * (dk + params.sensorPrecision));
    double cError = 0.001 * edge->measurement().norm();
    edge->information()(1,1) = 1.0 / (cError * cError);

    Eigen::Rotation2Dd rot(beamAngle);
    Eigen::Matrix2d mrot = rot.toRotationMatrix();
    edge->information() = mrot * edge->information() * mrot.transpose();
  }