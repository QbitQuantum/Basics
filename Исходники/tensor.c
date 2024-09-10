int compute_abf(double x, double y, long *mat, double *a, double *b, double *f)
{
  long i, j, substeps, type0, half ;
  double angle ;
  double x1, y1 ;
  double m11,m22,m12, m21, lambda_small, lambda, lambda1, lambda2 ;
  double rs1, rs2, q1, q2, n11, n12, n22, r1, r2 ;
  double x4   = 0.0 ;
	double y4   = 0.0 ;
	double x2   = 0.0 ;
	double y2   = 0.0 ;
	double x2y2 = 0.0 ;
	double a_down, a_top ;
	double b_down, b_top ;
	double tx, ty ;

  type0 = get_mat_type(x, y) ;
  *mat = type0;

  angle = (2*PI) / ((double) lines) ;
  substeps = (radius / step) + 1 ; 

#if 0
  fprintf (msgout,"angle = %e substeps = %li (%e|%e)\n", angle, substeps, radius, step);
#endif

  for  (i=0; i<lines; i++) 
  {
    for  (j=0; j<substeps; j++) 
    {
      get_cyl_dir(step*((double)j), ((double) i)*angle, x, y, &x1, &y1) ;

      xi[i] = x1 ;
      yi[i] = y1 ;
      ri[i] = step*((double)j) ;

      /*printf("[%e, %e] => [%e, %e]\n",step*((double)j), ((double)i)*angle, x1, y1);*/

      if (get_mat_type(x1, y1) != type0) 
      { 
        break ; 
      }
    }
  }

  half = (long) (lines/2) ;

  for  (i=0; i<half; i++) 
  {
    if (ri[i] >= ri[i+half])
    {
      ri[i] = ri[i+half] ;
      get_cyl_dir(ri[i], angle*(double)(i),x,y,&xi[i],&yi[i]) ;
    }
    else 
    {
      ri[i+half] = ri[i] ;
      get_cyl_dir(ri[i], angle*(double)(i+half),x,y,&xi[i+half],&yi[i+half]) ;
    }
  }

#if 0
  for  (i=0; i<lines; i++) { printf("%e %e\n",xi[i], yi[i]); }
#endif
#if 0
  for  (i=0; i<lines; i++) { printf("%li %e \n",i, ri[i]); }
#endif


  m11 = 0.0 ;
  m22 = 0.0 ;
  m12 = 0.0 ;
  m21 = 0.0 ;

  for (i=0; i<lines; i++) 
  {
    m11 += pow ( (xi[i] - x), 2 ) ;
    m22 += pow ( (yi[i] - y), 2 ) ;

    m12 +=  pow((xi[i] - x),2) * pow((yi[i] - y),2) ;
  }

  m11 = m11 / lines ;
  m22 = m22 / lines ;
  m12 = m12 / lines ;
  m21 = m12 ;

  q1 = (m11+m22) ;
	q2 = sqrt( pow(m11+m22, 2) + 4.0*(m12*m21-m11*m22) );

	lambda1 = 0.5 * (q1 + q2 ) ;
	lambda2 = 0.5 * (q1 - q2 ) ;


	/* getting larger one: */
	if (lambda2 > lambda1) 
	{ 
		lambda       = lambda2 ; 
		lambda_small = lambda1 ; 
	}
	else                   
	{ 
		lambda       = lambda1 ; 
		lambda_small = lambda2 ; 
	}

#if 0
	/* eigenvector for larger eigenvalue */
	n11 = m11 - lambda ;
	n22 = m22 - lambda ;
	n12 = m12 ;

	r1 = (n11*n22)/n12 - n12 ;
	r2 = (-1.0)* (n11/n12) ;

	/* eigenvector for smaller eigenvalue */
	n11 = m11 - lambda_small ;
	n22 = m22 - lambda_small ;
	n12 = m12 ;

	rs1 = 1 ;
	rs2 = 0 ;
	/*
	rs1 = (n11*n22)/n12 - n12 ;
	rs2 = (-1.0)* (n11/n12) ;
	*/
#else
		r1 = lambda -m22 ;
		r2 = m12 ;
		rs1 = 1 ;
		rs2 = 0 ;
		/*
		rs1 = lambda_small -m22 ;
		rs2 =  m12 ;
		*/

		/*
		rs1 = -m22 ;
		rs2 = m11 - lambda_small ;
		*/
#endif

	if ( ( sqrt(r1*r1 + r2*r2) * sqrt(rs1*rs1 + rs2*rs2) ) == 0.0 )
	{
		*f = 0.0 ;
	}
	else 
	{
		*f = acos (
		 	(r1*rs1 + r2*rs2) / ( sqrt(r1*r1 + r2*r2) * sqrt(rs1*rs1 + rs2*rs2) )
			) ;
	}


  /* ################################ */
  *a = 0.0 ;
	*b = 0.0 ;

	/* transform coordinates: */
	for (i=0; i<lines; i++) 
	{
		xi[i] -= x ;
		yi[i] -= y ;
	}

	for (i=0; i<lines; i++) 
	{
		tx = xi[i] ;
		ty = yi[i] ;
		
		xi[i] = tx * cos ((*f)) + ty * sin ((*f)) ;
		yi[i] = -tx * sin ((*f)) + ty * cos ((*f)) ;
	}

	for (i=0; i<lines; i++)
	{
		x2   += pow(xi[i],2) ;
		x4   += pow(xi[i],4) ;

		y2   += pow(yi[i],2) ;
		y4   += pow(yi[i],4) ;

		x2y2 += (pow(xi[i],2)*pow(yi[i],2)) ;
	}

	a_top  = (x2y2*x2y2) - (x4*y4) ;
	a_down = (x2y2*y2)   - (x2*y4) ;

	if ((a_down == 0.0))
	{
		fprintf(msgout,"[E] %s: a =%f / %f!\n",
				("Computation of tensor scale failed"),
			 	a_top, a_down);
    *a = 0 ;
	}
  else
  {
    if ((a_top/a_down) > 0)
    {
	    *a = sqrt ( (a_top / a_down) ) ;
    }
    else
    {
      *a = 0 ;
    }
  }

	b_top  = (x2y2*x2y2) - (x4*y4) ;
	b_down = (x2*x2y2)   - (x4*y2) ;

	if ((b_down == 0.0))
	{
		fprintf(msgout,"[E] %s: b =%f / %f!\n",
				("Computation of tensor scale failed"),
			 	b_top, b_down);
    *b = 0 ;
	}
  else
  {
    if ((b_top/b_down) > 0)
    {
	    *b = sqrt ( (b_top / b_down) ) ;
    }
    else
    {
      *b = 0 ;
    }
  }

  return(0);
}