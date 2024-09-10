int main(int argc, char ** argv) {
    
    /* BEGIN DECLARATIONS */
    
    WINFO wi;        /* struct for command line input */
    
    /* workspace */
    
    float * v;       /* velocity field */
    float * p1;      /* pressure field, current time step */
    float * p0;      /* pressure field, last time step */
    
    float * tr;      /* storage for traces */
    float * tmp;     /* used to swap p1 and p0 */
    
    int ix, it;      /* counters */
    int isrc;        /* source counter */
    int imf;         /* movie frame counter */
    int isx;         /* source location, in units of dx */
    int nxz;         /* number of spatial grid points */
    /* int nz;          local number of gridpoints */
    int ntr;         /* number of traces */
    int nsam;        /* number of trace samples */
    int nsrc;        /* number of shots */
    float rz,rx,s;   /* precomputed coefficients */
    float vmax,vmin; /* max, min velocity values */
    /* float two;        two */
    
    /* END DECLARATIONS */
    
    sf_init(argc,argv);
    
    /* read inputs from command line */
    getinputs(true,&wi);
    
    /* compute number of shots */
    nsrc = (wi.isxend-wi.isxbeg)/(wi.iskip); nsrc++;
    
    /* compute number of spatial grid points */
    nxz=wi.nx * wi.nz;
    
    /* compute number of traces, samples in each record */
    ntr=wi.igxend-wi.igxbeg+1;
    nsam=ntr*wi.nt;
    
    /* allocate, initialize p0, p1, v, traces */
    p0=sf_floatalloc(nxz);
    p1=sf_floatalloc(nxz);
    v =sf_floatalloc(nxz);
    tr=sf_floatalloc(nsam);
    
    /* read velocity */
    sf_floatread(v,nxz,wi.vfile);
    
    /* CFL, sanity checks */
    vmax=fgetmax(v,nxz);
    vmin=fgetmin(v,nxz);
    if (vmax*wi.dt>CFL*fmaxf(wi.dx,wi.dz)) {
	sf_warning("CFL criterion violated");
	sf_warning("vmax=%e dx=%e dz=%e dt=%e\n",vmax,wi.dx,wi.dz,wi.dt);
	sf_error("max permitted dt=%e\n",CFL*fmaxf(wi.dx,wi.dz)/vmax);
    }
    if (vmin<=0.0) 
	sf_error("min velocity nonpositive");
    
    /* only square of velocity array needed from here on */
    fsquare(v,nxz);
    
    /* precalculate some coefficients */
    rz=wi.dt*wi.dt/(wi.dz*wi.dz);
    rx=wi.dt*wi.dt/(wi.dx*wi.dx);
    s =2.0*(rz+rx);
/*    two=2.0;
      nz=wi.nz; */
    
    /* shot loop */
    isrc=0;
    isx=wi.isxbeg;
    while (isx <= wi.isxend) {
	
	/* initialize pressure fields, traces */
	fzeros(p0,nxz);
	fzeros(p1,nxz);
	fzeros(tr,nsam);
	
	/* initialize movie frame counter */
	imf=0;
	
	/* time loop */
	for (it=0;it<wi.nt;it++) {
	    
	    /* construct next time step, overwrite on p0 */
	    
	    step_forward(p0,p1,v,wi.nz,wi.nx,rz,rx,s);
	    
	    /* tack on source */
	    p0[wi.isz+isx*wi.nz]+=fgetrick(it*wi.dt,wi.freq);
	    
	    /* swap pointers */
	    tmp=p0;
	    p0=p1;
	    p1=tmp;
	    
	    /* store trace samples if necessary */
	    if (NULL != wi.tfile) 
		for (ix=0;ix<ntr;ix++) 
		    tr[ix*wi.nt+it]=p1[(wi.igxbeg+ix)*wi.nz+wi.igz];
	    
	    /* write movie snap to file if necessary */
	    if (NULL != wi.mfile && wi.nm && !(it%wi.nm)) {
		sf_floatwrite(p1,nxz,wi.mfile);
		imf++;
	    }
	    
	    /* next t */
	}

	/* write traces to file if necessary */
	if (NULL != wi.tfile) 
	    sf_floatwrite(tr,nsam,wi.tfile);
	
	isx += wi.iskip;
	isrc++;
    } 


    exit(0);
}