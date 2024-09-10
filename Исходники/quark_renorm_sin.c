int quark_renorm( void ) {
register int i, dir;
register site *s;
int j, cgn;
Real mass_x2, finalrsq;
Real pix, piy, piz, pit;
Real sin_pmu, q_mu, prop_a, prop_b, z_fac, m_func, ftmp = 0;
Real r1, r2, r3;
int pmu, px, py, pz, pt;
int pxn, pyn, pzn, ptn;
int currentnode;
int j1, jm2, k, dirs[4];
msg_tag *mtag[2];
int j_mass;
su3_vector **psim = NULL;
int xi, j2, j3, j4, parity;
  imp_ferm_links_t **fn;

int multiflag;
FILE *fp_mom_ks[MAX_NUM_MASS];	/* for writing mom propagator files */
char filename[50];
 int prec = PRECISION;   /* Make internal precision for CG the same as
			    the prevailing precision */

    pix = 2.*PI / (Real)nx;
    piy = 2.*PI / (Real)ny;
    piz = 2.*PI / (Real)nz;
    pit = 2.*PI / (Real)nt;

    cgn = 0;

    if( num_mass == 1){
	multiflag = 0;
    }
    else{
	multiflag = 1;
	psim = (su3_vector **)malloc(num_mass*sizeof(su3_vector *));
	for(j=0; j<num_mass; j++){
	    psim[j] = (su3_vector *)malloc(sites_on_node*sizeof(su3_vector));
	}
    }

    /* Open the momentum propagator files */
    if(this_node == 0){
	for(j=0; j<num_mass; j++){
	    sprintf(filename,"mom_pt_prop.m_%d",j);
	    fp_mom_ks[j] = fopen(filename, "ab");
	    if(fp_mom_ks[j] == NULL){
		printf("quark_renorm: Node %d can't open file %s, error %d\n",
		       this_node,filename,errno);fflush(stdout);
		terminate(1);
	    }
	}
    }

    rephase( ON );	/* Turn staggered phases on */

    /* Create fat and long links */
    restore_fermion_links_from_site(fn_links, PRECISION);
    fn = get_fm_links(fn_links);
    /* If we want HISQ support, we need the Naik term epsilon index
        here for now we use fn[0] only, which has no epsilon
        correction. */

    /* Loop over the 16 source points */
    for(xi=0; xi<16; xi++){

	/* Initialize color trace of the propagator */
	FORALLSITES(i,s){
	    for(j=0; j<num_mass; j++){
		s->trace_prop[j].real = 0.0;
		s->trace_prop[j].imag = 0.0;
	    }
	}

	j1 = xi%2;
	k = xi/2;
	j2 = k%2;
	k /= 2;
	j3 = k%2;
	k /= 2;
	j4 = k%2;
	parity = (j1+j2+j3+j4)%2;
/*	dirs[XUP] = j1;
	dirs[YUP] = j2;
	dirs[ZUP] = j3;
	dirs[TUP] = j4; */

	/* Loop over colors of source vector */
	for(j=0; j<3; j++){

	    /* initialize the source in phi */
	    FORALLSITES(i,s){
		clearvec( &(s->phi));
	    }

	    /* Point source at site xi in the hypercube at origin */
	    if( node_number(j1,j2,j3,j4) == this_node ){
		i=node_index(j1,j2,j3,j4);
		lattice[i].phi.c[j].real = -1.0;
	    }

	    if( multiflag == 0){
		for(j_mass=0; j_mass<num_mass; j_mass++){
		    FORALLSITES(i,s){
			clearvec( &(s->xxx1));
		    }

		    if(parity == 0){
			/* do a C.G. (source in phi, result in xxx1) */
		      cgn += ks_congrad( F_OFFSET(phi), F_OFFSET(xxx1),
					 mass[j_mass], niter, nrestart, 
					 rsqprop,  PRECISION, 
					 EVEN, &finalrsq, fn[0]);
		      /* Multiply by -Madjoint */
		      dslash_site( F_OFFSET(xxx1), F_OFFSET(ttt), ODD,
				   fn[0]);
		      mass_x2 = 2.*mass[j_mass];
		      FOREVENSITES(i,s){
			scalar_mult_su3_vector( &(s->xxx1), -mass_x2,
						&(s->ttt));
		      }
		    }
		    else{