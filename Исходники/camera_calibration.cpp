GVector::vector3d< double > CameraParameters::getWorldLocation() {
  Quaternion<double> q;
  q.set(q0->getDouble(),q1->getDouble(),q2->getDouble(),q3->getDouble());
  q.invert();
  GVector::vector3d<double> v_in(tx->getDouble(),ty->getDouble(),tz->getDouble());
  v_in = (-(v_in));
  GVector::vector3d<double> v_out = q.rotateVectorByQuaternion(v_in);
  return v_out;
}