  void DrawableCloud::draw() {
    if(_parameter->show() && _cloud) {
      glPushMatrix();
      glMultMatrixf(_transformation.data());
      if(_drawablePoints)
	_drawablePoints->draw();
      if(_drawableNormals)
	_drawableNormals->draw();
      if(_drawableCovariances)
	_drawableCovariances->draw();
      if(_drawableCorrespondences)
	_drawableCorrespondences->draw();

      glPushMatrix();
      Eigen::Isometry3f sensorOffset;
      sensorOffset.translation() = Eigen::Vector3f(0.0f, 0.0f, 0.0f);
      Eigen::Quaternionf quaternion = Eigen::Quaternionf(-.5f, -0.5f, 0.5f, 0.5f);
      sensorOffset.linear() = quaternion.toRotationMatrix();
      sensorOffset.matrix().row(3) << 0.0f, 0.0f, 0.0f, 1.0f;
      glMultMatrixf(sensorOffset.data());
      glColor4f(1,0,0,0.5);
      glPopMatrix();

      glPopMatrix();
    }
  }