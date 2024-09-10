double
vpHomography::computeDisplacement(unsigned int nbpoint,
                                  vpPoint *c1P,
                                  vpPoint *c2P,
                                  vpPlane *oN,
                                  vpHomogeneousMatrix &c2Mc1,
                                  vpHomogeneousMatrix &c1Mo,
                                  int userobust
                                 )
{


  vpColVector e(2) ;
  double r_1 = -1 ;



  vpColVector p2(3) ;
  vpColVector p1(3) ;
  vpColVector Hp2(3) ;
  vpColVector Hp1(3) ;

  vpMatrix H2(2,6) ;
  vpColVector e2(2) ;
  vpMatrix H1(2,6) ;
  vpColVector e1(2) ;


  int only_1 = 1 ;
  int only_2 = 0 ;
  int iter = 0 ;
  unsigned int i ;
  unsigned int n=0 ;
  n = nbpoint ;
  if ((only_1==1) || (only_2==1))  ; else n *=2 ;

  vpRobust robust(n);
  vpColVector res(n) ;
  vpColVector w(n) ;
  w =1 ;
  robust.setThreshold(0.0000) ;
  vpMatrix W(2*n,2*n)  ;
  W = 0 ;

  vpColVector N1(3), N2(3) ;
  double d1, d2 ;

  double r =1e10 ;
  iter =0 ;
  while (vpMath::equal(r_1,r,threshold_displacement) == false )
  {

    r_1 =r ;
    // compute current position


    //Change frame (current)
    vpHomogeneousMatrix c1Mc2, c2Mo ;
    vpRotationMatrix c1Rc2, c2Rc1  ;
    vpTranslationVector c1Tc2, c2Tc1 ;
    c1Mc2 = c2Mc1.inverse() ;
    c2Mc1.extract(c2Rc1) ;
    c2Mc1.extract(c2Tc1) ;
    c2Mc1.extract(c1Rc2) ;
    c1Mc2.extract(c1Tc2) ;

    c2Mo = c2Mc1*c1Mo ;



    vpMatrix L(2,3), Lp ;
    int k =0 ;
    for (i=0 ; i < nbpoint ; i++)
    {
      getPlaneInfo(oN[i], c1Mo, N1, d1) ;
      getPlaneInfo(oN[i], c2Mo, N2, d2) ;
      p2[0] = c2P[i].get_x() ;
      p2[1] = c2P[i].get_y() ;
      p2[2] = 1.0 ;
      p1[0] = c1P[i].get_x() ;
      p1[1] = c1P[i].get_y() ;
      p1[2] = 1.0 ;

      vpMatrix H(3,3) ;

      Hp2 = ((vpMatrix)c1Rc2 + ((vpMatrix)c1Tc2*N2.t())/d2)*p2 ;  // p2 = Hp1
      Hp1 = ((vpMatrix)c2Rc1 + ((vpMatrix)c2Tc1*N1.t())/d1)*p1 ;  // p1 = Hp2

      Hp2 /= Hp2[2] ;  // normalisation
      Hp1 /= Hp1[2] ;


      // set up the interaction matrix
      double x = Hp2[0] ;
      double y = Hp2[1] ;
      double Z1  ;

      Z1 = (N1[0]*x+N1[1]*y+N1[2])/d1 ;        // 1/z


      H2[0][0] = -Z1 ;  H2[0][1] = 0  ;       H2[0][2] = x*Z1 ;
      H2[1][0] = 0 ;     H2[1][1] = -Z1 ;     H2[1][2] = y*Z1 ;
      H2[0][3] = x*y ;   H2[0][4] = -(1+x*x) ; H2[0][5] = y ;
      H2[1][3] = 1+y*y ; H2[1][4] = -x*y ;     H2[1][5] = -x ;
      H2 *=-1 ;

      vpMatrix c1CFc2(6,6) ;
      {
        vpMatrix sTR = c1Tc2.skew()*(vpMatrix)c1Rc2 ;
        for (unsigned int k=0 ; k < 3 ; k++)
          for (unsigned int l=0 ; l<3 ; l++)
          {
            c1CFc2[k][l] = c1Rc2[k][l] ;
            c1CFc2[k+3][l+3] = c1Rc2[k][l] ;
            c1CFc2[k][l+3] = sTR[k][l] ;
          }
      }
      H2 = H2*c1CFc2 ;



      // Set up the error vector
      e2[0] = Hp2[0] - c1P[i].get_x() ;
      e2[1] = Hp2[1] - c1P[i].get_y() ;

      x = Hp1[0] ;
      y = Hp1[1] ;

      Z1 = (N2[0]*x+N2[1]*y+N2[2])/d2 ; // 1/z

      H1[0][0] = -Z1 ;  H1[0][1] = 0  ;       H1[0][2] = x*Z1 ;
      H1[1][0] = 0 ;     H1[1][1] = -Z1 ;     H1[1][2] = y*Z1;
      H1[0][3] = x*y ;   H1[0][4] = -(1+x*x) ; H1[0][5] = y ;
      H1[1][3] = 1+y*y ; H1[1][4] = -x*y ;     H1[1][5] = -x ;

      // Set up the error vector
      e1[0] = Hp1[0] - c2P[i].get_x() ;
      e1[1] = Hp1[1] - c2P[i].get_y() ;


      if (only_2==1)
      {
        if (k == 0) { L = H2 ; e = e2 ; }
        else
        {
          L = vpMatrix::stackMatrices(L,H2) ;
          e = vpMatrix::stackMatrices(e,e2) ;
        }
      }
      else
        if (only_1==1)
        {
          if (k == 0) { L = H1 ; e= e1 ; }
          else
          {
            L = vpMatrix::stackMatrices(L,H1) ;
            e = vpMatrix::stackMatrices(e,e1) ;
          }
        }
        else
        {
          if (k == 0) {L = H2 ; e = e2 ; }
          else
          {
            L = vpMatrix::stackMatrices(L,H2) ;
            e = vpMatrix::stackMatrices(e,e2) ;
          }
          L = vpMatrix::stackMatrices(L,H1) ;
          e = vpMatrix::stackMatrices(e,e1) ;
        }


      k++ ;
    }

    if (userobust)
    {
      robust.setIteration(0);
      for (unsigned int k=0 ; k < n ; k++)
      {
        res[k] = vpMath::sqr(e[2*k]) + vpMath::sqr(e[2*k+1]) ;
      }
      robust.MEstimator(vpRobust::TUKEY, res, w);


      // compute the pseudo inverse of the interaction matrix
      for (unsigned int k=0 ; k < n ; k++)
      {
        W[2*k][2*k] = w[k] ;
        W[2*k+1][2*k+1] = w[k] ;
      }
    }
    else
    {
      for (unsigned int k=0 ; k < 2*n ; k++) W[k][k] = 1 ;
    }
    (W*L).pseudoInverse(Lp, 1e-16) ;
    // Compute the camera velocity
    vpColVector c2Tcc1 ;

    c2Tcc1 = -1*Lp*W*e  ;

    // only for simulation

    c2Mc1 = vpExponentialMap::direct(c2Tcc1).inverse()*c2Mc1 ; ;
    //   UpdatePose2(c2Tcc1, c2Mc1) ;
    r =(W*e).sumSquare() ;



  if (r < 1e-15)  {break ; }
    if (iter>1000){break ; }
    if (r>r_1) {  break ; }
    iter++ ;
  }

  return (W*e).sumSquare() ;

}