 void
 SDFRigidTransform::setLocalToWorld(const AffineTransform &t)
 {
     _worldToLocal = t.inverse();
 }