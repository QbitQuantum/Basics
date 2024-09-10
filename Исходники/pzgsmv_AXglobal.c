int pzgsmv_AXglobal_setup
(
 SuperMatrix *A,       /* Matrix A permuted by columns (input).
			  The type of A can be:
			  Stype = SLU_NCP; Dtype = SLU_Z; Mtype = SLU_GE. */
 Glu_persist_t *Glu_persist, /* input */
 gridinfo_t *grid,     /* input */
 int_t *m,             /* output */
 int_t *update[],      /* output */
 doublecomplex *val[],        /* output */
 int_t *bindx[],       /* output */
 int_t *mv_sup_to_proc /* output */
 )
{
    int n;
    int input_option;
    int N_update;    /* Number of variables updated on this process (output) */
    int iam = grid->iam;
    int nprocs = grid->nprow * grid->npcol;
    int_t *xsup = Glu_persist->xsup;
    int_t *supno = Glu_persist->supno;
    int_t nsupers;
    int i, nsup, p, t1, t2, t3;


    /* Initialize the list of global indices.
     * NOTE: the list of global indices must be in ascending order.
     */
    n = A->nrow;
    input_option = SUPER_LINEAR;
    nsupers = supno[n-1] + 1;

#if ( DEBUGlevel>=2 )
    if ( !iam ) {
	PrintInt10("xsup", supno[n-1]+1, xsup);
	PrintInt10("supno", n, supno);
    }
#endif

    if ( input_option == SUPER_LINEAR ) { /* Block partitioning based on
					     individual rows.  */
	/* Figure out mv_sup_to_proc[] on all processes. */
	for (p = 0; p < nprocs; ++p) {
	    t1 = n / nprocs;       /* Number of rows */
	    t2 = n - t1 * nprocs;  /* left-over, which will be assigned
				      to the first t2 processes.  */
	    if ( p >= t2 ) t2 += (p * t1); /* Starting row number */
	    else { /* First t2 processes will get one more row. */
 	        ++t1;              /* Number of rows. */
		t2 = p * t1;       /* Starting row. */
	    }
	    /* Make sure the starting and ending rows are at the
	       supernode boundaries. */
	    t3 = t2 + t1;      /* Ending row. */
	    nsup = supno[t2];
	    if ( t2 > xsup[nsup] ) { /* Round up the starting row. */
		t1 -= xsup[nsup+1] - t2;
		t2 = xsup[nsup+1];
	    }
	    nsup = supno[t3];
	    if ( t3 > xsup[nsup] ) /* Round up the ending row. */
		t1 += xsup[nsup+1] - t3;
	    t3 = t2 + t1 - 1;
	    if ( t1 ) {
		for (i = supno[t2]; i <= supno[t3]; ++i) {
		    mv_sup_to_proc[i] = p;
#if ( DEBUGlevel>=3 )
		    if ( mv_sup_to_proc[i] == p-1 ) {
			fprintf(stderr, 
				"mv_sup_to_proc conflicts at supno %d\n", i);
			exit(-1);
		    }
#endif
		}
	    }
	    
	    if ( iam == p ) {
		N_update = t1;
		if ( N_update ) {
		    if ( !(*update = intMalloc_dist(N_update)) )
			ABORT("Malloc fails for update[]");
		}
		for (i = 0; i < N_update; ++i) (*update)[i] = t2 + i;
#if ( DEBUGlevel>=3 )
		printf("(%2d) N_update = %4d\t"
		       "supers %4d to %4d\trows %4d to %4d\n",
		       iam, N_update, supno[t2], supno[t3], t2, t3);
#endif
	    }
	} /* for p ... */
    } else if ( input_option == SUPER_BLOCK ) { /* Block partitioning based on
						   individual supernodes.  */
	/* This may cause bad load balance, because the blocks are usually
	   small in the beginning and large toward the end.   */
	t1 = nsupers / nprocs;
	t2 = nsupers - t1 * nprocs; /* left-over */
	if ( iam >= t2 ) t2 += (iam * t1);
	else {
	    ++t1;          /* Number of blocks. */
	    t2 = iam * t1; /* Starting block. */
	}
	N_update = xsup[t2+t1] - xsup[t2];
	if ( !(*update = intMalloc_dist(N_update)) )
	    ABORT("Malloc fails for update[]");
	for (i = 0; i < N_update; ++i) (*update)[i] = xsup[t2] + i;
    }


    /* Create an MSR matrix in val/bindx to be used by pdgsmv(). */
    zcreate_msr_matrix(A, *update, N_update, val, bindx);

#if ( DEBUGlevel>=2 )
    PrintInt10("mv_sup_to_proc", nsupers, mv_sup_to_proc);
    zPrintMSRmatrix(N_update, *val, *bindx, grid);
#endif

    *m = N_update;
    return 0;
} /* PZGSMV_AXglobal_SETUP */