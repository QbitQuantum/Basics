SMetric3 buildMetricTangentToCurve(SVector3 &t, double l_t, double l_n)
{
  if (l_t == 0.0) return SMetric3(1.e-22);
  SVector3 a;
  if (fabs(t(0)) <= fabs(t(1)) && fabs(t(0)) <= fabs(t(2))){
    a = SVector3(1,0,0);
  }
  else if (fabs(t(1)) <= fabs(t(0)) && fabs(t(1)) <= fabs(t(2))){
    a = SVector3(0,1,0);
  }
  else{
    a = SVector3(0,0,1);
  }
  SVector3 b = crossprod (t,a);
  SVector3 c = crossprod (b,t);
  b.normalize();
  c.normalize();
  t.normalize();
  SMetric3 Metric (1./(l_t*l_t),1./(l_n*l_n),1./(l_n*l_n),t,b,c);
  //  printf("bmttc %g %g %g %g %g\n",l_t,l_n,Metric(0,0),Metric(0,1),Metric(1,1));
  return Metric;
}