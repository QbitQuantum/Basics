//dC/dt2 = -b2 + 3a1 + b1 = 
//  -3(p3-p2-p1+p2) + t1 + 4t2 + t3
//scale t2=t20*c
//dC/dc = t20^T [-3(p3-p1) + t1 + 4t2 + 4t3] = 0
//0.25* [t20^T 3(p3-p1) - t20^T(t1+t3)] = c*t20^T t20
//3/4 t20^T (p3-1/3*t3 - (p1+1/3t1)) = c*t20^T t20
void ConditionMiddleTangent(GeneralizedCubicBezierCurve& c1,GeneralizedCubicBezierCurve& c2)
{
  /*
  Vector a;
  c1.Accel(0,a);
  Real oldAccelStart = a.norm();
  c1.Accel(1,a);
  Real oldAccelMid = a.norm();
  c2.Accel(0,a);
  Real oldAccelMid2 = a.norm();
  c2.Accel(1,a);
  Real oldAccelEnd = a.norm();
  */

  Vector t20;
  c1.Deriv(1,t20);
  /*
  //HACK -- measure only for non-free floating robot joints
  for(int i=0;i<6;i++) t20(i) = 0;
  */
  if(t20.normSquared() < 1e-6) return;
  Vector topt1,topt2;
  if(c1.space) {
    c1.space->InterpolateDeriv(c1.x1,c1.x3,1.0,topt1);
    c2.space->InterpolateDeriv(c2.x0,c2.x2,0.0,topt2);
  }
  else {
    topt1 = (c1.x3-c1.x1);
    topt2 = (c2.x2-c2.x0);
  }
  Vector v = (topt2+topt1)*0.25;
  Real c = v.dot(t20)/dot(t20,t20);
  if(c < 0.1 || c > 0.5) {
    cout<<"Middle tangent scale (ideal 1/3): "<<c<<endl;
    getchar();
  }
  if(c1.space)
    c1.space->Integrate(c1.x3,t20*(-c),c1.x2);
  else
    c1.x2 = c1.x3 - c*t20;
  if(c2.space)
    c2.space->Integrate(c2.x0,t20*(-c),c2.x1);
  else
    c2.x1 = c2.x0 + c*t20;

  /*
  c1.Accel(0,a);
  Real newAccelStart = a.norm();
  c1.Accel(1,a);
  Real newAccelMid = a.norm();
  c2.Accel(0,a);
  Real newAccelMid2 = a.norm();
  c2.Accel(1,a);
  Real newAccelEnd = a.norm();
  */
  //printf("Accel change: %g %g %g %g -> %g %g %g %g\n",oldAccelStart,oldAccelMid,oldAccelMid2,oldAccelEnd,newAccelStart,newAccelMid,newAccelMid2,newAccelEnd);
  //getchar();
}