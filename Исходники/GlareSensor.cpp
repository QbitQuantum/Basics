  bool GlareSensor_Impl::setTransformation(const openstudio::Transformation& transformation) 
  {
    Vector3d translation = transformation.translation();
    this->setPositionXCoordinate(translation.x());
    this->setPositionYCoordinate(translation.y());
    this->setPositionZCoordinate(translation.z());

    EulerAngles eulerAngles = transformation.eulerAngles();
    setPsiRotationAroundXAxis(radToDeg(eulerAngles.psi()));
    setThetaRotationAroundYAxis(radToDeg(eulerAngles.theta()));
    setPhiRotationAroundZAxis(radToDeg(eulerAngles.phi()));
    
    return true;  
  }