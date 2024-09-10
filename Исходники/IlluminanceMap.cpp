  bool IlluminanceMap_Impl::setTransformation(const openstudio::Transformation& transformation) 
  {
    bool test;

    Vector3d translation = transformation.translation();
    this->setOriginXCoordinate(translation.x());
    this->setOriginYCoordinate(translation.y());
    this->setOriginZCoordinate(translation.z());

    EulerAngles eulerAngles = transformation.eulerAngles();
    test = this->setPsiRotationAroundXAxis(radToDeg(eulerAngles.psi()));
    OS_ASSERT(test);
    test = this->setThetaRotationAroundYAxis(radToDeg(eulerAngles.theta()));
    OS_ASSERT(test);
    test = this->setPhiRotationAroundZAxis(radToDeg(eulerAngles.phi()));
    OS_ASSERT(test);

    return true;
  }