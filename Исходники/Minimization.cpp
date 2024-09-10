ConvergenceResult ConstrainedMinimizationProblem::LineMinimizationStep(const Vector& dx,Real& alpha0)
{
  Vector x0 = x;
  Real fx0 = fx;
  const Real lineSearchShrink = 0.5;
  Real dxnorm = dx.norm();
  Real t = alpha0;
  Real slope = Abs(dx.dot(grad));
  if(dxnorm < tolgrad) {
    return ConvergenceF;
  }

  //if(verbose>=1 && t != alpha0) cout<<"Starting t value: "<<t<<endl;
  //find a step that descends along grad
  for(int lineSearchIters=0;;lineSearchIters++) {
    if(t*dxnorm < tolx) {
      if(verbose>=1) cout<<"ConstrainedMinimzationProblem::LineSearch(): Converged on t on line search iteration "<<lineSearchIters<<", |dx|="<<dxnorm<<endl;
      //x must remain on surface... just set x to x0
      x = x0; alpha0 = 0;
      return ConvergenceX;
    }
    x = x0; x.madd(dx,t);
    for(int i=0;i<x.n;i++)
      if(IsNaN(x(i))) {
	cerr<<"ConstrainedMinimizationProblem: x is NaN!"<<endl;
	cerr<<"t is "<<t<<endl;
	cerr<<"x0 is "<<x0<<endl;
	getchar();
	return ConvergenceError;
      }
    if(SolveFeasiblePoint(x,20)) {
      Assert(CheckPoint(x));
      fx = (*f)(x);
      if(fx < fx0 - ALF*slope*t) {
	break;
      }
    }
    else {
      if(verbose>=1) cout<<"ConstrainedMinimzationProblem::StepGD(): Warning, MoveToSurface_Bounded failed on line search iteration "<<lineSearchIters<<endl;
    }
    //reduce t
    t *= lineSearchShrink;
  }
  alpha0 = t;

  if(Abs(fx-fx0) <= tolf) {
    if(verbose>=1) cout<<"ConstrainedMinimzationProblem::StepGD(): Success, change in f is "<<fx0-fx<<endl;
    return ConvergenceF;
  }

  if(verbose>=1) cout<<"StepGD(): Target "<<fx<<", length of gradient "<<dxnorm<<", step size "<<t*dxnorm<<endl;

  if(bmin.n != 0)
    Assert(AABBContains(x0,bmin,bmax));

  return MaxItersReached;
}