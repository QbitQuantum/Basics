void float_eulers_of_quat(struct FloatEulers *e, struct FloatQuat *q)
{
  const float qx2  = q->qx * q->qx;
  const float qy2  = q->qy * q->qy;
  const float qz2  = q->qz * q->qz;
  const float qiqx = q->qi * q->qx;
  const float qiqy = q->qi * q->qy;
  const float qiqz = q->qi * q->qz;
  const float qxqy = q->qx * q->qy;
  const float qxqz = q->qx * q->qz;
  const float qyqz = q->qy * q->qz;
  const float dcm00 = 1.0 - 2.*(qy2 +  qz2);
  const float dcm01 =       2.*(qxqy + qiqz);
  const float dcm02 =       2.*(qxqz - qiqy);
  const float dcm12 =       2.*(qyqz + qiqx);
  const float dcm22 = 1.0 - 2.*(qx2 +  qy2);

  e->phi = atan2f(dcm12, dcm22);
  e->theta = -asinf(dcm02);
  e->psi = atan2f(dcm01, dcm00);
}