int
vpPose::calculArbreDementhon(vpMatrix &b, vpColVector &U,
                             vpHomogeneousMatrix &cMo)
{

#if (DEBUG_LEVEL1)
  std::cout << "begin vpPose::CalculArbreDementhon() " << std::endl;
#endif

  unsigned int i, k;
  int erreur = 0;
  unsigned int cpt;
  double s,c,si,co;
  double smin,smin_old, s1,s2;
  double r, theta;
  vpHomogeneousMatrix  cMo1,cMo2,cMo_old;

  unsigned int iter_max = 20;
  vpMatrix eps(iter_max+1,npt) ;


  // on test si tous les points sont devant la camera
  for(i = 0; i < npt; i++)
  {
    double z ;
    z = cMo[2][0]*c3d[i].get_oX()+cMo[2][1]*c3d[i].get_oY()+cMo[2][2]*c3d[i].get_oZ() + cMo[2][3];
    if (z <= 0.0) erreur = -1;
  }

  smin = sqrt(computeResidualDementhon(cMo)/npt)  ;

  vpColVector xi(npt) ;
  vpColVector yi(npt) ;

  if (erreur==0)
  {
    k=0;
    for(i = 0; i < npt; i++)
    {
      xi[k] = c3d[i].get_x();
      yi[k] = c3d[i].get_y();

      if (k != 0)
      { // On ne prend pas le 1er point
        eps[0][k] = (cMo[2][0]*c3d[i].get_oX() +
          cMo[2][1]*c3d[i].get_oY() +
          cMo[2][2]*c3d[i].get_oZ())/cMo[2][3];
      }
      k++;
    }


    vpColVector I0(3) ;
    vpColVector J0(3) ;
    vpColVector I(3) ;
    vpColVector J(3) ;

    vpHomogeneousMatrix cMo_old ;
    smin_old = 2*smin ;

    cpt = 0;
    while ((cpt<20) && (smin_old > 0.01) && (smin <= smin_old))
    {
#if (DEBUG_LEVEL2)
      {
        std::cout << "cpt " << cpt << std::endl ;
        std::cout << "smin_old " << smin_old << std::endl ;
        std::cout << "smin " << smin << std::endl ;
      }
#endif

      smin_old = smin;
      cMo_old = cMo;

      I0 = 0 ;
      J0 = 0 ;

      for (i=1;i<npt;i++)
      {
        s = (1.0+eps[cpt][i])*xi[i] - xi[0];
        I0[0] += b[0][i-1] * s;
        I0[1] += b[1][i-1] * s;
        I0[2] += b[2][i-1] * s;
        s = (1.0+eps[cpt][i])*yi[i] - yi[0];
        J0[0] += b[0][i-1] * s;
        J0[1] += b[1][i-1] * s;
        J0[2] += b[2][i-1] * s;
      }

      s = -2.0*(vpColVector::dotProd(I0,J0));
      c = J0.sumSquare() - I0.sumSquare() ;

      calculRTheta(s,c,r,theta);
      co = cos(theta);
      si = sin(theta);

      /* 1ere branche	*/
      I = I0 + U*r*co ;
      J = J0 + U*r*si ;

#if (DEBUG_LEVEL3)
      {
        std::cout << "I " << I.t() ;
        std::cout << "J " << J.t() ;
      }
#endif

      calculSolutionDementhon(xi[0],yi[0],I,J,cMo1);
      s1 =  sqrt(computeResidualDementhon(cMo1)/npt)  ;
#if (DEBUG_LEVEL3)
      std::cout << "cMo1 "<< std::endl << cMo1 << std::endl ;
#endif

      /* 2eme branche	*/
      I = I0 - U*r*co ;
      J = J0 - U*r*si ;
#if (DEBUG_LEVEL3)
      {
        std::cout << "I " << I.t() ;
        std::cout << "J " << J.t() ;
      }
#endif

      calculSolutionDementhon(xi[0],yi[0],I,J,cMo2);
      s2 =  sqrt(computeResidualDementhon(cMo2)/npt)  ;
#if (DEBUG_LEVEL3)
      std::cout << "cMo2 "<< std::endl << cMo2 << std::endl ;
#endif

      cpt ++;
      if (s1 <= s2)
      {
        smin = s1;
        k = 0;
        for(i = 0; i < npt; i++)
        {
          if (k != 0) { // On ne prend pas le 1er point
            eps[cpt][k] = (cMo1[2][0]*c3d[i].get_oX() + cMo1[2][1]*c3d[i].get_oY()
              + cMo1[2][2]*c3d[i].get_oZ())/cMo1[2][3];
          }
          k++;
        }
        cMo = cMo1 ;
      }
      else
      {
        smin = s2;
        k = 0;
        for(i = 0; i < npt; i++)
        {
          if (k != 0) { // On ne prend pas le 1er point
            eps[cpt][k] = (cMo2[2][0]*c3d[i].get_oX() + cMo2[2][1]*c3d[i].get_oY()
              + cMo2[2][2]*c3d[i].get_oZ())/cMo2[2][3];
          }
          k++;
        }
        cMo = cMo2 ;
      }

      if (smin > smin_old)
      {
#if (DEBUG_LEVEL2) 
        std::cout << "Divergence "  <<  std::endl ;
#endif

        cMo = cMo_old ;
      }
#if (DEBUG_LEVEL2)
      {
        std::cout << "s1 = " << s1 << std::endl ;
        std::cout << "s2 = " << s2 << std::endl ;
        std::cout << "smin = " << smin << std::endl ;
        std::cout << "smin_old = " << smin_old << std::endl ;
      }
#endif
    }
  }
#if (DEBUG_LEVEL1)
  std::cout << "end vpPose::CalculArbreDementhon() return "<< erreur  << std::endl;
#endif

  return erreur ;
}