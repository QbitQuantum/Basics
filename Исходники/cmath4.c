void *
cx_deriv(void *data, short int type, int length, int *newlength, short int *newtype, struct plot *pl, struct plot *newpl, int grouping)
{
    double *scratch;
    double *spare;
    double x;
    int i, j, k;
    int	degree;
    int n, base;

    if (grouping == 0)
	grouping = length;
    /* First do some sanity checks. */
    if (!pl || !pl->pl_scale || !newpl || !newpl->pl_scale) {
        fprintf(cp_err, "Internal error: cx_deriv: bad scale\n");
        return (NULL);
    }

    if (!cp_getvar("dpolydegree", CP_NUM, (void *) &degree))
	degree = 2; /* default quadratic */

    n = degree +  1;

    spare = alloc_d(n);
    scratch = alloc_d(n * (n + 1));

    *newlength = length;
    *newtype = type;

    if (type == VF_COMPLEX) {
	complex *c_outdata, *c_indata;
	double *r_coefs, *i_coefs;
	double *scale;

	r_coefs = alloc_d(n);
	i_coefs = alloc_d(n);
	c_indata = (complex *) data;
	c_outdata = alloc_c(length);
	scale = alloc_d(length);	/* XXX */
	if (pl->pl_scale->v_type == VF_COMPLEX)
	    /* Not ideal */
	  for (i = 0; i < length; i++)
		   scale[i] = realpart(&pl->pl_scale->v_compdata[i]);
	 else
	    for (i = 0; i < length; i++)
		   scale[i] = pl->pl_scale->v_realdata[i];

	 for (base = 0; base < length; base += grouping)
    {
	    k = 0;
	    for (i = degree; i < grouping; i += 1)
       {

		  /* real */
		  for (j = 0; j < n; j++)
		    spare[j] = c_indata[j + i + base].cx_real;
		  if (!ft_polyfit(scale + i + base - degree,
		    spare, r_coefs, degree, scratch))
		   {
		    fprintf(stderr, "ft_polyfit @ %d failed\n", i);
		   }
		  ft_polyderiv(r_coefs, degree);

		  /* for loop gets the beginning part */
		  for (j = k; j <= i + degree / 2; j++)
        {
		    x = scale[j + base];
		    c_outdata[j + base].cx_real =
			ft_peval(x, r_coefs, degree - 1);
		  }

		  /* imag */
		  for (j = 0; j < n; j++)
		    spare[j] = c_indata[j + i + base].cx_imag;
		  if (!ft_polyfit(scale + i - degree + base,
		    spare, i_coefs, degree, scratch))
		  {
		    fprintf(stderr, "ft_polyfit @ %d failed\n", i);
		  }
		  ft_polyderiv(i_coefs, degree);

		  /* for loop gets the beginning part */
        for (j = k; j <= i - degree / 2; j++)
        {
		    x = scale[j + base];
		    c_outdata[j + base].cx_imag =
		    ft_peval(x, i_coefs, degree - 1);
		  }
		 k = j;
	   }

	    /* get the tail */
	    for (j = k; j < length; j++)
       {
		  x = scale[j + base];
		  /* real */
		  c_outdata[j + base].cx_real = ft_peval(x, r_coefs, degree - 1);
		  /* imag */
		  c_outdata[j + base].cx_imag = ft_peval(x, i_coefs, degree - 1);
	    }
    }

	tfree(r_coefs);
	tfree(i_coefs);
	tfree(scale);
	return (void *) c_outdata;

  }
  else
  {
	/* all-real case */
	double *coefs;

	double *outdata, *indata;
	double *scale;

	coefs = alloc_d(n);
	indata = (double *) data;
	outdata = alloc_d(length);
	scale = alloc_d(length);	/* XXX */

   /* Here I encountered a problem because when we issue an instruction like this:
    * plot -deriv(vp(3)) to calculate something similar to the group delay, the code
    * detects that vector vp(3) is real and it is believed that the frequency is also 
    * real. The frequency is COMPLEX and the program aborts so I'm going to put the 
    * check that the frequency is complex vector not to abort.
    */


   /* Original problematic code
	* for (i = 0; i < length; i++)
	*    scale[i] = pl->pl_scale->v_realdata[i];
    */

   /* Modified to deal with complex frequency vector */
   if (pl->pl_scale->v_type == VF_COMPLEX)
	  for (i = 0; i < length; i++)
		   scale[i] = realpart(&pl->pl_scale->v_compdata[i]);
	else
	    for (i = 0; i < length; i++)
		   scale[i] = pl->pl_scale->v_realdata[i];



	for (base = 0; base < length; base += grouping)
   {
	    k = 0;
	    for (i = degree; i < grouping; i += 1)
       {
		  if (!ft_polyfit(scale + i - degree + base,
		    indata + i - degree + base, coefs, degree, scratch))
		   {
		    fprintf(stderr, "ft_polyfit @ %d failed\n", i + base);
	    	}
        ft_polyderiv(coefs, degree);

		  /* for loop gets the beginning part */
		  for (j = k; j <= i - degree / 2; j++)
        {
          /* Seems the same problem because the frequency vector is complex
           * and the real part of the complex should be accessed because if we 
           * run x = pl-> pl_scale-> v_realdata [base + j]; the execution will 
           * abort.
           */

          if (pl->pl_scale->v_type == VF_COMPLEX)
            x = realpart(&pl->pl_scale->v_compdata[j+base]);  /* For complex scale vector */
          else
            x = pl->pl_scale->v_realdata[j + base];           /* For real scale vector */

		    outdata[j + base] = ft_peval(x, coefs, degree - 1);
		  }
	    	k = j;
	    }

	    for (j = k; j < length; j++)
       {
          /* Again the same error */
		  /* x = pl->pl_scale->v_realdata[j + base]; */
          if (pl->pl_scale->v_type == VF_COMPLEX)
            x = realpart(&pl->pl_scale->v_compdata[j+base]);  /* For complex scale vector */
          else
            x = pl->pl_scale->v_realdata[j + base];           /* For real scale vector */

		    outdata[j + base] = ft_peval(x, coefs, degree - 1);
	    }
   }


	tfree(coefs);
	tfree(scale);	/* XXX */
	return (char *) outdata;
 }

}