void jac_quat3_euler3(Eigen::Matrix<double, 6, 6>& J, const SE3Quat& t)
{
  const Vector3d& tr0 = t.translation();
  const Quaterniond& q0 = t.rotation();

  double delta=1e-6;
  double idelta= 1. / (2. * delta);

  for (int i=0; i<6; i++){
    SE3Quat ta, tb;
    if (i<3){
      Vector3d tra=tr0;
      Vector3d trb=tr0;
      tra[i] -= delta;
      trb[i] += delta;
      ta = SE3Quat(q0, tra); 
      tb = SE3Quat(q0, trb); 
    } else {
      Quaterniond qa=q0;
      Quaterniond qb=q0;
      if (i == 3) {
        qa.x() -= delta;
        qb.x() += delta;
      }
      else if (i == 4) {
        qa.y() -= delta;
        qb.y() += delta;
      }
      else if (i == 5) {
        qa.z() -= delta;
        qb.z() += delta;
      }
      qa.normalize();
      qb.normalize();
      ta = SE3Quat(qa, tr0); 
      tb = SE3Quat(qb, tr0); 
    }

    Vector3d dtr = (tb.translation() - ta.translation())*idelta;
    Vector3d taAngles, tbAngles;
    quat_to_euler(ta.rotation(), taAngles(2), taAngles(1), taAngles(0));
    quat_to_euler(tb.rotation(), tbAngles(2), tbAngles(1), tbAngles(0));
    Vector3d da = (tbAngles - taAngles) * idelta; //TODO wraparounds not handled

    for (int j=0; j<6; j++){
      if (j<3){
        J(j, i) = dtr(j);
      } else {
        J(j, i) = da(j-3);
      }
    }
  }
}