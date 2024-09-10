void Win3D::drag(int _x, int _y) {
  double deltaX = _x - mMouseX;
  double deltaY = _y - mMouseY;

  mMouseX = _x;
  mMouseY = _y;

  if (mRotate) {
    if (deltaX != 0 || deltaY != 0)
      mTrackBall.updateBall(_x, mWinHeight - _y);
  }
  if (mTranslate) {
    Eigen::Matrix3d rot = mTrackBall.getRotationMatrix();
    mTrans += rot.transpose()*Eigen::Vector3d(deltaX, -deltaY, 0.0);
  }
  if (mZooming) {
    mZoom += deltaY*0.01;
  }
  glutPostRedisplay();
}