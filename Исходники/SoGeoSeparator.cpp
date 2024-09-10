// Doc from superclass.
void
SoGeoSeparator::getMatrix(SoGetMatrixAction * action)
{
  SbMatrix m = this->getTransform(action->getState());
  action->getMatrix() = m;
  action->getInverse() = m.inverse();
}