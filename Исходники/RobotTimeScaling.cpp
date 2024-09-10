bool CheckBounds(Robot& robot,const TimeScaledBezierCurve& traj,Real dt)
{
  Real T=traj.EndTime();
  int numdivs = (int)Ceil(T/dt);
  vector<Real> times(numdivs);
  for(int i=0;i<numdivs;i++) 
    times[i] = T*Real(i)/Real(numdivs-1);  
  return CheckBounds(robot,traj,times);
}