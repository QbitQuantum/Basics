/*! \COININTERNAL */
void
SoCenterballDragger::valueChangedCB(void *, SoDragger * d)
{
  SoCenterballDragger * thisp = static_cast<SoCenterballDragger *>(d);
  SbMatrix matrix = thisp->getMotionMatrix();
  SbVec3f t, s;
  SbRotation r, so;

  // Eliminate center variable of matrix
  if (thisp->savedcenter != SbVec3f(0.0f, 0.0f, 0.0f)) {
    SbMatrix trans;
    trans.setTranslate(thisp->savedcenter);
    matrix.multLeft(trans);
    trans.setTranslate(-(thisp->savedcenter));
    matrix.multRight(trans);
  }

  // Do an inverse rotation, using matrix with center eliminated
  // to obtain correct translation
  matrix.getTransform(t, r, s, so);
  SbMatrix rotmat;
  rotmat.setRotate(r);
  //SbMatrix tmp = matrix;
  matrix.multLeft(rotmat.inverse());

  // Update center of object if dragger has translated
  SbVec3f difftrans(matrix[3][0], matrix[3][1], matrix[3][2]);
  if (difftrans != SbVec3f(0.0f, 0.0f, 0.0f)) {
    thisp->centerFieldSensor->detach();
    thisp->center.setValue(thisp->savedcenter + difftrans);
    thisp->centerFieldSensor->attach(&thisp->center);
  }

  thisp->rotFieldSensor->detach();
  if (thisp->rotation.getValue() != r) {
    thisp->rotation = r;
  }
  thisp->rotFieldSensor->attach(&thisp->rotation);
}