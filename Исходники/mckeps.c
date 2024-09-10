void SolveKEps(short kimp, int tinc, double sh, double bu, double tr,
   double Km, double *tke, double *eps)
{
  int it, nit = 0;
  double pr, a, b, c, d, ets;
  const double c1 = 1.44, c2 = 1.92, tol = 0.00000001, mu = 0.09;
  const double tkemin = 0.001, epsmin = 0.000001;
  double c3, sb, Ea, epsa;
  double t1, t4, t5, t6, t7, t8, t9, t11, t20;
  c3 = c2 - 1.;
  if (!kimp)  {
/*   Analytical Version:  Explicit K */
/*    if (sh + bu > 0. && Km < 1.)  Km = 1.;
    sh *= Km; bu *= Km; */
    pr = sh + bu/* + PP(tr)*/;
    ets = *tke + tinc*(sh + bu);
    a = tinc*c3;
    b = ets + tinc*(*eps - c1*pr);
    c = -*eps * ets;
    d = b*b - 4.*a*c;
    if (d < 0.)  {
      *eps = epsmin;
      *tke = tkemin;
    }
    else  {
      *eps = (-b + sqrt(d)) / (2.*a);
      *tke = ets - tinc * *eps;
      if (*eps < epsmin)  *eps = epsmin;
      if (*tke < tkemin)  *tke = tkemin;
    }
  }
  else  {
/*
  Analytical Version: Implicit K:  
  The following formulae have been obtained with MapleV:
*/
    pr = sh + PP(bu);
    tr = PP(tr);
    sb = sh + bu;
    if (!*tke || !*eps)  {
      *tke = tkemin;
      *eps = epsmin;
    }
    Ea = *tke; epsa = *eps;
    t1 = c1*pr;
    t5 = c1*c1;
    t6 = pr*pr;
    t8 = t1*sb;
    t9 = sb*sb;
    t11 = mu*mu;
    t20 = tinc*tinc;
    a = ((sb-t1)*mu*c3+((t5*t6-2.*t8+t9)*t11+(2.*(t9-t8)*t11+
	t11*t9*c3)*c3)*t20)*tinc;
    b = -c3*epsa+(-2.*c2*mu*sb*epsa+((2.-c2)*tr*mu*sb+pr*mu*(2.*epsa-
	tr*c1))*c1)*t20+(-mu*sb*c2+(2.0*pr*c2-pr)*mu*c1)*tinc*Ea;
    t1 = epsa*epsa;
    t4 = c1*c1;
    t5 = tr*tr;
    t7 = sb*mu;
    t8 = tinc*tinc;
    c = (t1-epsa*tr*c1-t4*t5*t7*t8)*tinc+((2.*c2-1.)*epsa+
	(tr*c2*t7+pr*mu*tr*c1)*c1*t8-tinc*c1*pr*mu*c2*Ea)*Ea;
    d = (epsa*tinc*c1*tr-Ea*c2*epsa)*Ea;
    if (a == 0.)  {
      fprintf(stderr, "a is equal to zero in SolveKEps. Leaving\n");
      exit (0);
    }
    *tke = SolveCubic(b/a, c/a, d/a);
    *eps = *tke *(*tke *mu * tinc *(c1*pr - c2*sb) + epsa) /
        	 (-*tke * c3 + c2*Ea - tinc * c1 * tr);
    if (*tke <= tkemin)  *tke = tkemin;
    if (*eps < epsmin)  *eps = epsmin;
  }
}