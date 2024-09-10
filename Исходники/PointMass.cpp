void PointMass::draw(renderer::RenderInterface* _ri,
                     const Eigen::Vector4d& _color,
                     bool _useDefaultColor) const
{
  if (_ri == NULL)
    return;

  _ri->pushMatrix();

  // render the self geometry
//  mParentJoint->applyGLTransform(_ri);
  Eigen::Isometry3d T = Eigen::Isometry3d::Identity();
  T.translation() = mX;
  _ri->transform(T);
  Eigen::Vector4d color1;
  color1 << 0.8, 0.3, 0.3, 1.0;
  mShape->draw(_ri, color1, false);
  _ri->popMatrix();

//  _ri->pushName((unsigned)mID);
  _ri->pushMatrix();
  T.translation() = mX0;
  _ri->transform(T);
  Eigen::Vector4d color2;
  color2 << 0.3, 0.8, 0.3, 1.0;
  mShape->draw(_ri, color2, false);
  _ri->popMatrix();
//  _ri->popName();

}