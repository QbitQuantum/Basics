F32 Rigid::getKineticEnergy()
{
   Point3F w;
   QuatF qmat = angPosition;
   qmat.inverse();
   qmat.mulP(angVelocity,&w);
   const F32* f = invObjectInertia;
   return 0.5f * ((mass * mDot(linVelocity,linVelocity)) +
      w.x * w.x / f[0] +
      w.y * w.y / f[5] +
      w.z * w.z / f[10]);
}