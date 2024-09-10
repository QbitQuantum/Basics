int
main(int argc, char **argv)
{
	int nt;		/* number of time samples per trace */
	float dt;	/* time sampling interval */
	float ft;	/* time of first sample */
	int it;		/* time sample index */
	int cdpmin;	/* minimum cdp to process */
	int cdpmax;	/* maximum cdp to process */
	float dx;	/* cdp sampling interval */
	int nx;		/* number of cdps to process */
	int nxfft;	/* number of cdps after zero padding for fft */
	int nxpad;	/* minimum number of cdps for zero padding */
	int ix;		/* cdp index, starting with ix=0 */
	int noffmix;	/* number of offsets to mix */
	float *tdmo;	/* times at which rms velocities are specified */
	float *vdmo;	/* rms velocities at times specified in tdmo */
	float sdmo;	/* DMO stretch factor */
	int ntdmo;	/* number tnmo values specified */
	int itdmo;	/* index into tnmo array */
	int nvdmo;	/* number vnmo values specified */
	float fmax;	/* maximum frequency */
	float *vrms;	/* uniformly sampled vrms(t) */
	float **p;	/* traces for one offset - common-offset gather */
	float **q;	/* DMO-corrected and mixed traces to be output */
	float offset;	/* source-receiver offset of current trace */
	float oldoffset;/* offset of previous trace */
	int noff;	/* number of offsets processed in current mix */
	int ntrace;	/* number of traces processed in current mix */
	int itrace;	/* trace index */
	int gottrace;	/* non-zero if an input trace was read */
	int done;	/* non-zero if done */
	int verbose;	/* =1 for diagnostic print */
	char *tmpdir;	/* directory path for tmp files	*/
	cwp_Bool istmpdir=cwp_false;/* true for user given path */

	/* hook up getpar */
	initargs(argc, argv);
	requestdoc(1);

	/* get information from the first header */
	if (!gettr(&tr)) err("can't get first trace");
	nt = tr.ns;
	dt = ((double) tr.dt)/1000000.0;
	ft = tr.delrt/1000.0;
	offset = tr.offset;

	/* get parameters */
	if (!getparint("cdpmin",&cdpmin)) err("must specify cdpmin");
	if (!getparint("cdpmax",&cdpmax)) err("must specify cdpmax");
	if (cdpmin>cdpmax) err("cdpmin must not be greater than cdpmax");
	if (!getparfloat("dxcdp",&dx)) err("must specify dxcdp");
	if (!getparint("noffmix",&noffmix)) err("must specify noffmix");
	ntdmo = countparval("tdmo");
	if (ntdmo==0) ntdmo = 1;
	tdmo = ealloc1float(ntdmo);
	if (!getparfloat("tdmo",tdmo)) tdmo[0] = 0.0;
	nvdmo = countparval("vdmo");
	if (nvdmo==0) nvdmo = 1;
	if (nvdmo!=ntdmo) err("number of tdmo and vdmo must be equal");
	vdmo = ealloc1float(nvdmo);
	if (!getparfloat("vdmo",vdmo)) vdmo[0] = 1500.0;
	for (itdmo=1; itdmo<ntdmo; ++itdmo)
		if (tdmo[itdmo]<=tdmo[itdmo-1])
			err("tdmo must increase monotonically");
	if (!getparfloat("sdmo",&sdmo)) sdmo = 1.0;
	if (!getparfloat("fmax",&fmax)) fmax = 0.5/dt;
	if (!getparint("verbose",&verbose)) verbose=0;
	
	/* Look for user-supplied tmpdir */
	if (!getparstring("tmpdir",&tmpdir) &&
	    !(tmpdir = getenv("CWP_TMPDIR"))) tmpdir="";
	if (!STREQ(tmpdir, "") && access(tmpdir, WRITE_OK))
		err("you can't write in %s (or it doesn't exist)", tmpdir);
	
	/* make uniformly sampled rms velocity function of time */
	vrms = ealloc1float(nt);
	mkvrms(ntdmo,tdmo,vdmo,nt,dt,ft,vrms);
	
	/* determine number of cdps to process */
	nx = cdpmax-cdpmin+1;
	
	/* allocate and zero common-offset gather p(t,x) */
	nxpad = 0.5*ABS(offset/dx);
	nxfft = npfar(nx+nxpad);
	p = ealloc2float(nt,nxfft+2);
	for (ix=0; ix<nxfft; ++ix)
		for (it=0; it<nt; ++it)
			p[ix][it] = 0.0;

	/* allocate and zero offset mix accumulator q(t,x) */
	q = ealloc2float(nt,nx);
	for (ix=0; ix<nx; ++ix)
		for (it=0; it<nt; ++it)
			q[ix][it] = 0.0;
		
	/* open temporary file for headers */
	if (STREQ(tmpdir,"")) {
		headerfp = etmpfile();
		if (verbose) warn("using tmpfile() call");
	} else { /* user-supplied tmpdir */
		char directory[BUFSIZ];
		strcpy(directory, tmpdir);
		strcpy(headerfile, temporary_filename(directory));
		/* Trap signals so can remove temp files */
		signal(SIGINT,  (void (*) (int)) closefiles);
		signal(SIGQUIT, (void (*) (int)) closefiles);
		signal(SIGHUP,  (void (*) (int)) closefiles);
		signal(SIGTERM, (void (*) (int)) closefiles);
		headerfp = efopen(headerfile, "w+");
      		istmpdir=cwp_true;		
		if (verbose)
			warn("putting temporary header file in %s", directory);
	}

	/* initialize */
	oldoffset = offset;
	gottrace = 1;
	done = 0;
	ntrace = 0;
	noff = 0;

	/* loop over traces */
	do {
		/* if got a trace, determine offset */
		if (gottrace) offset = tr.offset;
		
		/* if an offset is complete */
		if ((gottrace && offset!=oldoffset) || !gottrace) {
		
			/* do dmo for old common-offset gather */
			dmooff(oldoffset,fmax,sdmo,nx,dx,nt,dt,ft,vrms,p);
			
			/* add dmo-corrected traces to mix */
			for (ix=0; ix<nx; ++ix)
				for (it=0; it<nt; ++it)
					q[ix][it] += p[ix][it];
			
			/* count offsets in mix */
			noff++;
							
			/* free space for old common-offset gather */
			free2float(p);
			
			/* if beginning a new offset */
			if (offset!=oldoffset) {
				
				/* allocate space for new offset */
				nxpad = 0.5*ABS(offset/dx);
				nxfft = npfar(nx+nxpad);
				p = ealloc2float(nt,nxfft+2);
				for (ix=0; ix<nxfft; ++ix)
					for (it=0; it<nt; ++it)
						p[ix][it] = 0.0;
			}
		}
		
		/* if a mix of offsets is complete */
		if (noff==noffmix || !gottrace) {
			
			/* rewind trace header file */
			erewind(headerfp);
			
			/* loop over all output traces */
			for (itrace=0; itrace<ntrace; ++itrace) {
			
				/* read trace header and determine cdp index */
				efread(&tro,HDRBYTES,1,headerfp);
				
				/* get dmo-corrected data */
				memcpy( (void *) tro.data,
					(const void *)	q[tro.cdp-cdpmin],
					nt*sizeof(float));
				
				/* write output trace */
				puttr(&tro);
			}
			
			/* report */
			if (verbose) 
				fprintf(stderr,"\tCompleted mix of "
					"%d offsets with %d traces\n",
					noff,ntrace);
			
			/* if no more traces, break */
			if (!gottrace) break;
			
			/* rewind trace header file */
			erewind(headerfp);

			/* reset number of offsets and traces in mix */
			noff = 0;
			ntrace = 0;
			
			/* zero offset mix accumulator */
			for (ix=0; ix<nx; ++ix)
				for (it=0; it<nt; ++it)
					q[ix][it] = 0.0;
		}
			
		/* if cdp is within range to process */
		if (tr.cdp>=cdpmin && tr.cdp<=cdpmax) {
	
			/* save trace header and update number of traces */
			efwrite(&tr,HDRBYTES,1,headerfp);
			ntrace++;

			/* remember offset */
			oldoffset = offset;

			/* get trace samples */
			memcpy( (void *) p[tr.cdp-cdpmin],
				   (const void *) tr.data, nt*sizeof(float));
		}

		/* get next trace (if there is one) */
		if (!gettr(&tr)) gottrace = 0;
		
	} while (!done);

	/* clean up */
	efclose(headerfp);
	if (istmpdir) eremove(headerfile);
	return(CWP_Exit());
}