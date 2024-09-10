  bool PlanarSurfaceGroup_Impl::setTransformation(const openstudio::Transformation& transformation) {

    EulerAngles eulerAngles = transformation.eulerAngles();
    if ((eulerAngles.psi() != 0) || (eulerAngles.theta() != 0)){
      return false;
    }

    double dORN = -radToDeg(eulerAngles.phi());
    this->setDirectionofRelativeNorth(dORN, false);

    Vector3d translation = transformation.translation();
    this->setXOrigin(translation.x(), false);
    this->setYOrigin(translation.y(), false);
    this->setZOrigin(translation.z(), false);
    this->emitChangeSignals();

    return true;
  }