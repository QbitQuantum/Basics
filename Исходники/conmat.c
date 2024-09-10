/* Both ellipses are assumed to have non-zero radii */
int Int2Elip(Point *IntPts,Ellipse *E1,Ellipse *E2)
   {
   TMat ElpCirMat1,ElpCirMat2,InvMat,TempMat;
   Conic Conic1,Conic2,Conic3,TempConic;
   double Roots[3],qRoots[2];
   static Circle TestCir = {{0.0,0.0},1.0};
   Line TestLine[2];
   Point TestPoint;
   double PolyCoef[4];		/* coefficients of the polynomial */
   double D;			/* discriminant: B^2 - AC */
   double Phi;			/* ellipse rotation */
   double m,n;			/* ellipse translation */
   double Scl;			/* scaling factor */
   int NumRoots,NumLines;
   int CircleInts;		/* intersections between line and circle */
   int IntCount = 0;		/* number of intersections found */
   int i,j,k;

   /* compute the transformations which turn E1 and E2 into circles */
   Elp2Cir(E1,&ElpCirMat1);
   Elp2Cir(E2,&ElpCirMat2);

   /* compute the inverse transformation of ElpCirMat1 */
   InvElp2Cir(E1,&InvMat);

   /* Compute the characteristic matrices */
   GenEllipseCoefs(E1,&Conic1);
   GenEllipseCoefs(E2,&Conic2);

   /* Find x such that Det(Conic1 + x Conic2) = 0 */
   PolyCoef[0] = -Conic1.C*Conic1.D*Conic1.D + 2.0*Conic1.B*Conic1.D*Conic1.E -
      Conic1.A*Conic1.E*Conic1.E - Conic1.B*Conic1.B*Conic1.F +
      Conic1.A*Conic1.C*Conic1.F;
   PolyCoef[1] = -(Conic2.C*Conic1.D*Conic1.D) -
      2.0*Conic1.C*Conic1.D*Conic2.D + 2.0*Conic2.B*Conic1.D*Conic1.E +
      2.0*Conic1.B*Conic2.D*Conic1.E - Conic2.A*Conic1.E*Conic1.E +
      2.0*Conic1.B*Conic1.D*Conic2.E - 2.0*Conic1.A*Conic1.E*Conic2.E -
      2.0*Conic1.B*Conic2.B*Conic1.F + Conic2.A*Conic1.C*Conic1.F +
      Conic1.A*Conic2.C*Conic1.F - Conic1.B*Conic1.B*Conic2.F +
      Conic1.A*Conic1.C*Conic2.F;
   PolyCoef[2] = -2.0*Conic2.C*Conic1.D*Conic2.D - Conic1.C*Conic2.D*Conic2.D +
      2.0*Conic2.B*Conic2.D*Conic1.E + 2.0*Conic2.B*Conic1.D*Conic2.E +
      2.0*Conic1.B*Conic2.D*Conic2.E - 2.0*Conic2.A*Conic1.E*Conic2.E -
      Conic1.A*Conic2.E*Conic2.E - Conic2.B*Conic2.B*Conic1.F +
      Conic2.A*Conic2.C*Conic1.F - 2.0*Conic1.B*Conic2.B*Conic2.F +
      Conic2.A*Conic1.C*Conic2.F + Conic1.A*Conic2.C*Conic2.F;
   PolyCoef[3] = -Conic2.C*Conic2.D*Conic2.D + 2.0*Conic2.B*Conic2.D*Conic2.E -
      Conic2.A*Conic2.E*Conic2.E - Conic2.B*Conic2.B*Conic2.F +
      Conic2.A*Conic2.C*Conic2.F;
   NumRoots = SolveCubic(PolyCoef,Roots);

   if (NumRoots == 0)
      return 0;

   /* we try all the roots, even though it's redundant, so that we
      avoid some pathological situations */
   for (i=0;i<NumRoots;i++)
      {
      NumLines = 0;

      /* Conic3 = Conic1 + mu Conic2 */
      Conic3.A = Conic1.A + Roots[i]*Conic2.A;
      Conic3.B = Conic1.B + Roots[i]*Conic2.B;
      Conic3.C = Conic1.C + Roots[i]*Conic2.C;
      Conic3.D = Conic1.D + Roots[i]*Conic2.D;
      Conic3.E = Conic1.E + Roots[i]*Conic2.E;
      Conic3.F = Conic1.F + Roots[i]*Conic2.F;

      D = Conic3.B*Conic3.B - Conic3.A*Conic3.C;
      if (IsZero(Conic3.A) && IsZero(Conic3.B) && IsZero(Conic3.C))
	 {
	 /* Case 1 - Single line */
	 NumLines = 1;
	 /* compute endpoints of the line, avoiding division by zero */
	 if (fabs(Conic3.D) > fabs(Conic3.E))
	    {
	    TestLine[0].P1.Y = 0.0;
	    TestLine[0].P1.X = -Conic3.F/(Conic3.D + Conic3.D);
	    TestLine[0].P2.Y = 1.0;
	    TestLine[0].P2.X = -(Conic3.E + Conic3.E + Conic3.F)/
	       (Conic3.D + Conic3.D);
	    }
	 else
	    {
	    TestLine[0].P1.X = 0.0;
	    TestLine[0].P1.Y = -Conic3.F/(Conic3.E + Conic3.E);
	    TestLine[0].P2.X = 1.0;
	    TestLine[0].P2.Y = -(Conic3.D + Conic3.D + Conic3.F)/
	       (Conic3.E + Conic3.E);
	    }
	 }
      else
	 {
	 /* use the espresion for Phi that takes atan of the
	    smallest argument */
	 Phi = (fabs(Conic3.B + Conic3.B) < fabs(Conic3.A-Conic3.C)?
	    atan((Conic3.B + Conic3.B)/(Conic3.A - Conic3.C)):
	    M_PI_2 - atan((Conic3.A - Conic3.C)/(Conic3.B + Conic3.B)))/2.0;
	 if (IsZero(D))
	    {
	    /* Case 2 - Parallel lines */
	    TempConic = Conic3;
	    TempMat = IdentMat;
	    RotateMat(&TempMat,-Phi);
	    TransformConic(&TempConic,&TempMat);
	    if (IsZero(TempConic.C))   /* vertical */
	       {
	       PolyCoef[0] = TempConic.F;
	       PolyCoef[1] = 2*TempConic.D;
	       PolyCoef[2] = TempConic.A;
	       if ((NumLines=SolveQuadic(PolyCoef,qRoots))!=0)
		  {
		  TestLine[0].P1.X = qRoots[0];
		  TestLine[0].P1.Y = -1.0;
		  TestLine[0].P2.X = qRoots[0];
		  TestLine[0].P2.Y = 1.0;
		  if (NumLines==2)
		     {
		     TestLine[1].P1.X = qRoots[1];
		     TestLine[1].P1.Y = -1.0;
		     TestLine[1].P2.X = qRoots[1];
		     TestLine[1].P2.Y = 1.0;
		     }
		  }
	       }
	    else		    /* horizontal */
	       {
	       PolyCoef[0] = TempConic.F;
	       PolyCoef[1] = 2*TempConic.E;
	       PolyCoef[2] = TempConic.C;
	       if ((NumLines=SolveQuadic(PolyCoef,qRoots))!=0)
		  {
		  TestLine[0].P1.X = -1.0;
		  TestLine[0].P1.Y = qRoots[0];
		  TestLine[0].P2.X = 1.0;
		  TestLine[0].P2.Y = qRoots[0];
		  if (NumLines==2)
		     {
		     TestLine[1].P1.X = -1.0;
		     TestLine[1].P1.Y = qRoots[1];
		     TestLine[1].P2.X = 1.0;
		     TestLine[1].P2.Y = qRoots[1];
		     }
		  }
	       }
	    TempMat = IdentMat;
	    RotateMat(&TempMat,Phi);
	    TransformPoint(&TestLine[0].P1,&TempMat);
	    TransformPoint(&TestLine[0].P2,&TempMat);
	    if (NumLines==2)
	       {
	       TransformPoint(&TestLine[1].P1,&TempMat);
	       TransformPoint(&TestLine[1].P2,&TempMat);
	       }
	    }
	 else
	    {
	    /* Case 3 - Crossing lines */
	    NumLines = 2;

	    /* translate the system so that the intersection of the lines
	       is at the origin */
	    TempConic = Conic3;
	    m = (Conic3.C*Conic3.D - Conic3.B*Conic3.E)/D;
	    n = (Conic3.A*Conic3.E - Conic3.B*Conic3.D)/D;
	    TempMat = IdentMat;
	    TranslateMat(&TempMat,-m,-n);
	    RotateMat(&TempMat,-Phi);
	    TransformConic(&TempConic,&TempMat);

	    /* Compute the line endpoints */
	    TestLine[0].P1.X = sqrt(fabs(1.0/TempConic.A));
	    TestLine[0].P1.Y = sqrt(fabs(1.0/TempConic.C));
	    Scl = max(TestLine[0].P1.X,TestLine[0].P1.Y);  /* adjust range */
	    TestLine[0].P1.X /= Scl;
	    TestLine[0].P1.Y /= Scl;
	    TestLine[0].P2.X = - TestLine[0].P1.X;
	    TestLine[0].P2.Y = - TestLine[0].P1.Y;
	    TestLine[1].P1.X = TestLine[0].P1.X;
	    TestLine[1].P1.Y = - TestLine[0].P1.Y;
	    TestLine[1].P2.X = - TestLine[1].P1.X;
	    TestLine[1].P2.Y = - TestLine[1].P1.Y;

	    /* translate the lines back */
	    TempMat = IdentMat;
	    RotateMat(&TempMat,Phi);
	    TranslateMat(&TempMat,m,n);
	    TransformPoint(&TestLine[0].P1,&TempMat);
	    TransformPoint(&TestLine[0].P2,&TempMat);
	    TransformPoint(&TestLine[1].P1,&TempMat);
	    TransformPoint(&TestLine[1].P2,&TempMat);
	    }
	 }

      /* find the ellipse line intersections */
      for (j = 0;j < NumLines;j++)
	 {
	 /* transform the line endpts into the circle space of the ellipse */
	 TransformPoint(&TestLine[j].P1,&ElpCirMat1);
	 TransformPoint(&TestLine[j].P2,&ElpCirMat1);

	 /* compute the number of intersections of the transformed line
	    and test circle */
	 CircleInts = IntCirLine(&IntPts[IntCount],&TestCir,&TestLine[j]);
	 if (CircleInts>0)
	    {
	    /* transform the intersection points back into ellipse space */
	    for (k = 0;k < CircleInts;k++)
	       TransformPoint(&IntPts[IntCount+k],&InvMat);
	    /* update the number of intersections found */
	    IntCount += CircleInts;
	    }
	 }
      }
   /* validate the points */
   j = IntCount;
   IntCount = 0;
   for (i = 0;i < j;i++)
      {
      TestPoint = IntPts[i];
      TransformPoint(&TestPoint,&ElpCirMat2);
      if (TestPoint.X < 2.0 && TestPoint.Y < 2.0 &&
	 IsZero(1.0 - sqrt(TestPoint.X*TestPoint.X +
	 TestPoint.Y*TestPoint.Y)))
	 IntPts[IntCount++]=IntPts[i];
      }
   return IntCount;
   }