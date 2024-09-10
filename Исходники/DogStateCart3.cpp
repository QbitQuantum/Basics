bool DogStateCart3::check_valid_state() const
{
    const dTensorBC5& aux = *DogStateCart3::aux;
    const dTensorBC5& q = *DogStateCart3::q;
    const int mx   = q.getsize(1);
    const int my   = q.getsize(2);
    const int mz   = q.getsize(3);
    const int meqn = q.getsize(4);
    const int kmax = q.getsize(5);
    const int mbc  = q.getmbc();
    const int maux = aux.getsize(4);

    if(!debug_check_condition())
    {
        dprintf1("debug condition violated");
        return false;
    }

    bool okay=true;
    int bad_i=0, bad_j=0, bad_m=0, bad_k=0, bad_ell=0;

// TODO: it would be nice to only use a single pragma loop here  (-DS)
#pragma omp parallel for
    for (int i=1; i<=mx; i++)
        for (int j=1; j<=my; j++)
	  for (int k=1; k<=mz; k++)
            for (int m=1; m<=meqn; m++)
	      for (int ell=1; ell<=kmax; ell++)
                {
		  const double val = q.get(i,j,k,m,ell);
		  //assert_isfinite(val);
		  bool is_finite = val >= -DBL_MAX && val <= DBL_MAX;
		  if(!is_finite)
		    // a block preceeded by a critical directive
		    // of a given name can only be executed by a
		    // single thread at a time
		    // (omitting "(NaN)" would use default name)
#pragma omp critical (not_finite)
                    {
                        okay=false;
                        Wprintf("q(%d,%d,%d,%d) is not finite", i,j,k,m,ell);
                        bad_i = i;
                        bad_j = j;
			bad_k = k;
                        bad_m = m;
                        bad_ell = ell;
                    }
                }

    bool aux_okay = true;
    int aux_i=0, aux_j=0, aux_k=0, aux_m=0, aux_ell=0;
#pragma omp parallel for
    for (int i=1; i<=mx; i++)
        for (int j=1; j<=my; j++)
	  for (int k=1; k<=mz; k++)
            for (int m=1; m<=maux; m++)
	      for (int ell=1; ell<=kmax; ell++)
                {
		  const double val = aux.get(i,j,k,m,ell);
		  //assert_isfinite(val);
		  bool is_finite = val >= -DBL_MAX && val <= DBL_MAX;
		  if(!is_finite)
#pragma omp critical (not_finite)
                    {
		      aux_okay=false;
		      Wprintf("aux(%d,%d,%d,%d) is not finite", i,j,k,m,ell);
		      aux_i = i;
		      aux_j = j;
		      aux_k = k;
		      aux_m = m;
		      aux_ell = ell;
                    }
                }
    if(!okay || !aux_okay)
      {
        write_frame(9999,get_outputdir());
        if(!okay)
            errmsg_printf("at time %e q(%d,%d,%d,%d) is not finite", get_time(),
			  bad_i,bad_j,bad_k,bad_m,bad_ell);
        if(!aux_okay)
            errmsg_printf("at time %e aux(%d,%d,%d,%d) is not finite", get_time(),
			  aux_i,aux_j,aux_k,aux_m,aux_ell);
    }
    return true;
}