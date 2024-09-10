const Matrix&
J2BeamFiber2d::getTangent (void)
{
  double twoG = E/(1.0+nu);
  double G = 0.5*twoG;

  double sig[2];
  sig[0] = E*(Tepsilon(0)-epsPn[0]);
  sig[1] = G*(Tepsilon(1)-epsPn[1]);

  static const double one3 = 1.0/3;
  static const double two3 = 2.0*one3;
  static const double root23 = sqrt(two3);

  double two3Hkin = two3*Hkin;

  double xsi[2];
  //xsi[0] = sig[0] - two3*Hkin*1.5*epsPn[0];
  //xsi[1] = sig[1] - two3*Hkin*0.5*epsPn[1];
  xsi[0] = sig[0] -      Hkin*epsPn[0];
  xsi[1] = sig[1] - one3*Hkin*epsPn[1];

  double q = sqrt(two3*xsi[0]*xsi[0] + 2.0*xsi[1]*xsi[1]);
  double F = q - root23*(sigmaY + Hiso*alphan);

  if (F < -100*DBL_EPSILON) {
    D(0,0) = E;
    D(1,1) = G;
    D(0,1) = D(1,0) = 0.0;

    epsPn1[0] = epsPn[0];
    epsPn1[1] = epsPn[1];
  }
  else {

    // Solve for dg
    double dg = 0.0;

    static Vector R(3);
    R(0) = 0.0; R(1) = 0.0; R(2) = F;
    static Vector x(3);
    x(0) = xsi[0]; x(1) = xsi[1]; x(2) = dg;

    static Matrix J(3,3);
    static Vector dx(3);

    int iter = 0; int maxIter = 25;
    while (iter < maxIter && R.Norm() > sigmaY*1.0e-14) {
        iter++;

        J(0,0) = 1.0 + dg*two3*(E+Hkin); J(0,1) = 0.0;
        J(1,0) = 0.0; J(1,1) = 1.0 + dg*(twoG+two3Hkin);

        J(0,2) = two3*(E+Hkin)*x(0);
        J(1,2) = (twoG+two3Hkin)*x(1);

        //J(2,0) = x(0)*two3/q; J(2,1) = x(1)*2.0/q;
        J(2,0) = (1.0-two3*Hiso*dg)*x(0)*two3/q;
        J(2,1) = (1.0-two3*Hiso*dg)*x(1)*2.0/q;

        //J(2,2) = -root23*Hiso;
	J(2,2) = -two3*Hiso*q;

        J.Solve(R, dx);
        x.addVector(1.0, dx, -1.0);

        dg = x(2);
        dg_n1 = dg;

        q = sqrt(two3*x(0)*x(0) + 2.0*x(1)*x(1));

        R(0) = x(0) - xsi[0] + dg*two3*(E+Hkin)*x(0);
        R(1) = x(1) - xsi[1] + dg*(twoG+two3Hkin)*x(1);
        R(2) = q - root23*(sigmaY + Hiso*(alphan+dg*root23*q));
    }

    if (iter == maxIter) {
      //opserr << "J2BeamFiber2d::getTangent -- maxIter reached " << R.Norm() << endln;
    }

    alphan1 = alphan + dg*root23*q;

    epsPn1[0] = epsPn[0] + dg*two3*x(0);
    epsPn1[1] = epsPn[1] + dg*2.0*x(1);

    //J(2,0) = (1.0-two3*Hiso*dg)*x(0)*two3/q; J(2,1) = (1.0-two3*Hiso*dg)*x(1)*2.0/q;
    //J(2,2) = -two3*Hiso*q;
    //static Matrix invJ(3,3);
    //J.Invert(invJ);

    J(0,0) = 1.0 + dg*two3*E/(1.0+dg*two3Hkin); J(0,1) = 0.0;
    J(1,0) = 0.0; J(1,1) = 1.0 + dg*twoG/(1.0+dg*two3Hkin);

    J(0,2) = (two3*E-dg*two3*E/(1.0+dg*two3Hkin)*two3Hkin)*x(0);
    J(1,2) = (twoG  -dg*  twoG/(1.0+dg*two3Hkin)*two3Hkin)*x(1);

    //J(2,0) = x(0)/q*two3/(1.0+dg*two3Hkin);
    //J(2,1) = x(1)/q* 2.0/(1.0+dg*two3Hkin);
    J(2,0) = (1.0-two3*Hiso*dg)*x(0)/q*two3/(1.0+dg*two3Hkin);
    J(2,1) = (1.0-two3*Hiso*dg)*x(1)/q* 2.0/(1.0+dg*two3Hkin);

    //J(2,2) = -(x(0)/q*two3/(1.0+dg*two3Hkin)*two3Hkin*x(0))
    //         -(x(1)/q* 2.0/(1.0+dg*two3Hkin)*two3Hkin*x(1));
    //J(2,2) = -q*two3Hkin/(1.0+dg*two3Hkin) - root23*Hiso;
    J(2,2) = -q*two3Hkin/(1.0+dg*two3Hkin) - two3*Hiso*q;

    static Matrix invJ(3,3);
    J.Invert(invJ);

    D(0,0) = invJ(0,0)*E;
    D(1,0) = invJ(1,0)*E;
    D(0,1) = invJ(0,1)*G;
    D(1,1) = invJ(1,1)*G;
  }

  return D;
}