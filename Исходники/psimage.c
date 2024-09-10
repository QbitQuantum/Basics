int 
main (int argc, char **argv)
{
	int n1,n2,n1tic,n2tic,nfloats,bbox[4],
	  i1,i2,grid1,grid2,style,
	  n1c,n2c,n1s,n2s,i1beg,i1end,i2beg,i2end,i1c,i2c,
	  nz,iz,i1step,i2step,verbose,hls,bps,
	  legend,ugrid=SOLID,lstyle=VERTLEFT,lz,lbegsup=0,lendsup=0,ln=256,
	  lbbox[4], threecolor=0; /* BEREND, Schoenfelder */
        int lnice; /* c liner */
	float labelsize,titlesize,perc,clip,bperc,wperc,bclip,wclip,
		d1,f1,d2,f2,*z,*temp,zscale,zoffset,zi,
		xbox,ybox,width,height,
		x1beg,x1end,x2beg,x2end,
		x1min,x1max,x2min,x2max,
		d1num,f1num,d2num,f2num,
		p1beg,p1end,p2beg,p2end,matrix[6],colors[3][3], /* for 3 color mode */
		d1s,d2s,
	  lwidth,lheight,lx,ly,lbeg,lend,lmin=(float) FLT_MAX,lmax=(float) -FLT_MAX,
	  ldnum,lfnum,ld,lf=0,labmatrix[6]; /* BEREND, Schoenfelder */
	float axeswidth, ticwidth, gridwidth;
	unsigned char *cz,*czp,*sz,*data_legend=NULL;
	char *label1="",*label2="",*title="",*units="",
	  *legendfont="times_roman10",
	  *labelfont="Helvetica",*titlefont="Helvetica-Bold",
	  *styles="seismic",*grid1s="none",*grid2s="none",
	  *titlecolor="black",*axescolor="black",*gridcolor="black",
	  *lstyles="vertleft",*lgrids="none";
	FILE *infp=stdin;

	float **x1curve=NULL,**x2curve=NULL,*curvewidth=NULL;
	int i,j,curve=0,*npair=NULL,ncurvecolor=0,ncurvewidth=0,ncurvedash=0,*curvedash=NULL;
	char **curvecolor=NULL,**curvefile=NULL;
	FILE *curvefp=NULL;
	cwp_Bool is_curve = cwp_false;

	/* initialize getpar */
	initargs(argc,argv);
	requestdoc(1);

	/* get parameters describing 1st dimension sampling */
	if (!getparint("n1",&n1)) err("must specify n1!\n");
	d1 = 1.0;  getparfloat("d1",&d1);
	f1 = 0.0;  getparfloat("f1",&f1);
	x1min = (d1>0.0)?f1:f1+(n1-1)*d1;
	x1max = (d1<0.0)?f1:f1+(n1-1)*d1;

	/* get parameters describing 2nd dimension sampling */
	if (!getparint("n2",&n2)) {
		if (efseeko(infp,(off_t) 0,SEEK_END)!=0)
			err("must specify n2 if in a pipe!\n");
		nfloats = (int) (eftello(infp)/((off_t) sizeof(float)));
		efseeko(infp,(off_t) 0,SEEK_SET);
		n2 = nfloats/n1;
	}
	d2 = 1.0;  getparfloat("d2",&d2);
	f2 = 0.0;  getparfloat("f2",&f2);
	x2min = (d2>0.0)?f2:f2+(n2-1)*d2;
	x2max = (d2<0.0)?f2:f2+(n2-1)*d2;

	/* read color parameters */
	if (!getparint("threecolor",&threecolor)) threecolor=1;
	bps = 8;
	hls = 0;
	/* color[][0] is black, color[][2] is white in 2 color mode */
	colors[R][0] = colors[G][0] = colors[B][0] = 0.0;
	colors[R][1] = colors[G][1] = colors[B][1] = 0.5;
	colors[R][2] = colors[G][2] = colors[B][2] = 1.0;
	if (countparval("brgb") || countparval("wrgb")) {
		float brgb[3],grgb[3],wrgb[3];
		brgb[R] = brgb[G] = brgb[B] = 0.0;
		wrgb[R] = wrgb[G] = wrgb[B] = 1.0;
		getparfloat("brgb",&brgb[0]);
		getparfloat("wrgb",&wrgb[0]);
		grgb[R] = (brgb[R] + wrgb[R])/2.;
		grgb[G] = (brgb[G] + wrgb[G])/2.;
		grgb[B] = (brgb[B] + wrgb[B])/2.;
		if (threecolor==1)
		  getparfloat("grgb",&grgb[0]);
		brgb[R] = MAX(0.0,MIN(1.0,brgb[R]));
		grgb[R] = MAX(0.0,MIN(1.0,grgb[R]));
		wrgb[R] = MAX(0.0,MIN(1.0,wrgb[R]));
		brgb[G] = MAX(0.0,MIN(1.0,brgb[G]));
		grgb[G] = MAX(0.0,MIN(1.0,grgb[G]));
		wrgb[G] = MAX(0.0,MIN(1.0,wrgb[G]));
		brgb[B] = MAX(0.0,MIN(1.0,brgb[B]));
		grgb[B] = MAX(0.0,MIN(1.0,grgb[B]));
		wrgb[B] = MAX(0.0,MIN(1.0,wrgb[B]));
		colors[R][0] = brgb[R];	 colors[R][1] = grgb[R];  colors[R][2] = wrgb[R];
		colors[G][0] = brgb[G];	 colors[G][1] = grgb[G];  colors[G][2] = wrgb[G];
		colors[B][0] = brgb[B];	 colors[B][1] = grgb[B];  colors[B][2] = wrgb[B];
		if (!getparint("bps",&bps)) bps = 12;
		if (bps!=12 && bps!=24)
			err("bps must equal 12 or 24 for color plots!\n");
	} else if (countparval("bhls") || countparval("whls")) {
		float bhls[3],ghls[3],whls[3];
		hls = 1;
		bhls[H] = ghls[H] = whls[H] = 0.0;
		bhls[L] = 0.0;	ghls[L] = 0.5;	whls[L] = 1.0;
		bhls[S] = ghls[S] = whls[S] = 0.0;
		getparfloat("bhls",&bhls[0]);
		getparfloat("whls",&whls[0]);
		ghls[H] = (bhls[H] + whls[H])/2.;
		ghls[L] = (bhls[L] + whls[L])/2.;
		ghls[S] = (bhls[S] + whls[S])/2.;
		if (threecolor==1)
		  getparfloat("ghls",&ghls[0]);
		bhls[L] = MAX(0.0,MIN(1.0,bhls[L]));
		ghls[L] = MAX(0.0,MIN(1.0,ghls[L]));
		whls[L] = MAX(0.0,MIN(1.0,whls[L]));
		bhls[S] = MAX(0.0,MIN(1.0,bhls[S]));
		ghls[S] = MAX(0.0,MIN(1.0,ghls[S]));
		whls[S] = MAX(0.0,MIN(1.0,whls[S]));
		colors[H][0] = bhls[0];	 colors[H][1] = ghls[0];  colors[H][2] = whls[0];
		colors[L][0] = bhls[1];	 colors[L][1] = ghls[1];  colors[L][2] = whls[1];
		colors[S][0] = bhls[2];	 colors[S][1] = ghls[2];  colors[S][2] = whls[2];
		if (!getparint("bps",&bps)) bps = 12;
		if (bps!=12 && bps!=24)
			err("bps must equal 12 or 24 for color plots!\n");
	}

	/* get legend specs BEREND, Schoenfelder */
	legend = 0; getparint("legend", &legend); /* BEREND, Schoenfelder */
	getparstring("units", &units); /* BEREND, Schoenfelder */
	getparstring("legendfont", &legendfont);     /* BEREND, Schoenfelder */

	/* set up curve plotting */
	if ((curve=countparval("curve"))!=0) {
		curvefile=(char**)ealloc1(curve,sizeof(void*));
		getparstringarray("curve",curvefile);
		if ((x1curve=(float**)malloc(curve*sizeof(void*)))==NULL)
			err("Could not allocate x1curve pointers\n");
		if ((x2curve=(float**)malloc(curve*sizeof(void*)))==NULL)
			err("Could not allocate x2curve pointers\n");
		npair=ealloc1int(curve);
		getparint("npair",npair);
		is_curve = cwp_true;
	} else {
		npair=(int *)NULL;
		curvefile=(char **)NULL;
		x1curve=(float **)NULL;
		x2curve=(float **)NULL;
		is_curve = cwp_false;
	}
	if (is_curve) {
	 if ((ncurvecolor=countparval("curvecolor"))<curve) {
		curvecolor=(char**)ealloc1(curve,sizeof(void*));
		if (!getparstringarray("curvecolor",curvecolor)) {
			curvecolor[0]=(char *)cwp_strdup("black\0");
			ncurvecolor=1;
		}
		for (i=ncurvecolor; i<curve; i++)
			curvecolor[i]=(char *)cwp_strdup(curvecolor[ncurvecolor-1]);
	 } else if (ncurvecolor) {
		curvecolor=(char**)ealloc1(ncurvecolor,sizeof(void*));
		getparstringarray("curvecolor",curvecolor);
	 }
	 for (j=0; j<curve; j++) {
		curvefp=efopen(curvefile[j],"r");
		x1curve[j]=ealloc1float(npair[j]);
		x2curve[j]=ealloc1float(npair[j]);
		for (i=0; i<npair[j]; i++) {
			fscanf(curvefp,"%f",&x1curve[j][i]);
			fscanf(curvefp,"%f",&x2curve[j][i]);
		}
		efclose(curvefp);
	 }
	}

	/* read binary data to be plotted */
	nz = n1*n2;
	z = ealloc1float(nz);
	if (fread(z,sizeof(float),nz,infp)!=nz)
		err("error reading input file!\n");

	/* if necessary, determine clips from percentiles */
	if (getparfloat("clip",&clip)) {
		bclip = clip;
		wclip = -clip;
	}
	if ((!getparfloat("bclip",&bclip) || !getparfloat("wclip",&wclip)) &&
		!getparfloat("clip",&clip)) {
		perc = 100.0;  getparfloat("perc",&perc);
		temp = ealloc1float(nz);
		for (iz=0; iz<nz; iz++)
			temp[iz] = z[iz];
		if (!getparfloat("bclip",&bclip)) {
			bperc = perc;	getparfloat("bperc",&bperc);
			iz = (nz*bperc/100.0);
			if (iz<0) iz = 0;
			if (iz>nz-1) iz = nz-1;
			qkfind(iz,nz,temp);
			bclip = temp[iz];
		}
		if (!getparfloat("wclip",&wclip)) {
			wperc = 100.0-perc;  getparfloat("wperc",&wperc);
			iz = (nz*wperc/100.0);
			if (iz<0) iz = 0;
			if (iz>nz-1) iz = nz-1;
			qkfind(iz,nz,temp);
			wclip = temp[iz];
		}
		free1float(temp);
	}
	verbose = 1;  getparint("verbose",&verbose);
	if (verbose) warn("bclip=%g wclip=%g",bclip,wclip);

	/* get scaled sampling intervals */
	d1s = 1.0;  getparfloat("d1s",&d1s);
	d2s = 1.0;  getparfloat("d2s",&d2s);
	d1s = fabs(d1s);  d1s *= d1;
	d2s = fabs(d2s);  d2s *= d2;

	/* get axes parameters */
	xbox = 1.5; getparfloat("xbox",&xbox); /* if psimage is called by ximage, it */
	ybox = 1.5; getparfloat("ybox",&ybox); /* will xbox=1.166 and ybox=1.167 */
	width = 6.0; getparfloat("wbox",&width); getparfloat("width",&width);
	height = 8.0;getparfloat("hbox",&height);getparfloat("height",&height);
         /* begin c liner */
	lnice = 0;  getparint("lnice",&lnice); 
        if (lnice==1) {
            ybox = 2.2;
            /* lx=8 is set below, after getpar on lx ... c liner */
            width = 5.4;
            height = 7.2;
        }
         /* end c liner */
	x1beg = x1min; getparfloat("x1beg",&x1beg);
	x1end = x1max; getparfloat("x1end",&x1end);
	d1num = 0.0; getparfloat("d1num",&d1num);
	f1num = x1min; getparfloat("f1num",&f1num);
	n1tic = 1; getparint("n1tic",&n1tic);
	getparstring("grid1",&grid1s);
	if (STREQ("dot",grid1s))
		grid1 = DOT;
	else if (STREQ("dash",grid1s))
		grid1 = DASH;
	else if (STREQ("solid",grid1s))
		grid1 = SOLID;
	else
		grid1 = NONE;
	getparstring("label1",&label1);
	x2beg = x2min; getparfloat("x2beg",&x2beg);
	x2end = x2max; getparfloat("x2end",&x2end);
	d2num = 0.0; getparfloat("d2num",&d2num);
	f2num = 0.0; getparfloat("f2num",&f2num);
	n2tic = 1; getparint("n2tic",&n2tic);
	getparstring("grid2",&grid2s);
	if (STREQ("dot",grid2s))
		grid2 = DOT;
	else if (STREQ("dash",grid2s))
		grid2 = DASH;
	else if (STREQ("solid",grid2s))
		grid2 = SOLID;
	else
		grid2 = NONE;
	getparstring("label2",&label2);
	getparstring("labelfont",&labelfont);
	labelsize = 18.0; getparfloat("labelsize",&labelsize);
	getparstring("title",&title);
	getparstring("titlefont",&titlefont);
	titlesize = 24.0; getparfloat("titlesize",&titlesize);
	getparstring("titlecolor",&titlecolor);
	getparstring("axescolor",&axescolor);
	getparstring("gridcolor",&gridcolor);

	/* axes and tic width */
        if(!getparfloat("axeswidth",&axeswidth)) axeswidth=1;
        if (!getparfloat("ticwidth",&ticwidth)) ticwidth=axeswidth;
        if(!getparfloat("gridwidth",&gridwidth)) gridwidth =axeswidth;

	if (is_curve) {
	 if ((ncurvewidth=countparval("curvewidth"))<curve) {
		curvewidth=ealloc1float(curve);
		if (!getparfloat("curvewidth",curvewidth)) {
			curvewidth[0]=axeswidth;
			ncurvewidth=1;
		}
		for (i=ncurvewidth; i<curve; i++)
			curvewidth[i]=curvewidth[ncurvewidth-1];
	 } else {
		curvewidth=ealloc1float(ncurvewidth);
		getparfloat("curvewidth",curvewidth);
	 }
	 if ((ncurvedash=countparval("curvedash"))<curve) {
		curvedash=ealloc1int(curve);
		if (!getparint("curvedash",curvedash)) {
		        curvedash[0]=0;
			ncurvedash=1;
		}
		for (i=ncurvedash; i<curve; i++)
			curvedash[i]=curvedash[ncurvedash-1];
	 } else {
		curvedash=ealloc1int(ncurvedash);
		getparint("curvedash",curvedash);
	 }
	}

	getparstring("style",&styles);

	if (STREQ("normal",styles))
		style = NORMAL;
	else
		style = SEISMIC;

	/* Get or calc legend parameters */
	/* Legend min and max: Calc from data read in */
	if (legend) {
	  for (lz=0;lz<nz;lz++) {
	    lmin=FMIN(lmin,z[lz]);
	    lmax=FMAX(lmax,z[lz]);
	  }
	  if (verbose==2) warn("lmin=%g lmax=%g",lmin,lmax);
	}

	if (legend) {
	  lbeg = lmin; if (getparfloat("lbeg",&lbeg)) lbegsup=1;
	  lend = lmax; if (getparfloat("lend",&lend)) lendsup=1;


	  /* Change wclip,bclip to be inside legend range */
	  wclip = FMAX(lbeg,wclip); /* [wclip,bclip] has to be in [lbeg,lend] */
	  bclip = FMIN(lend,bclip);
	  if (lbegsup!=1) { /* Add white and black areas to show possible clipping */ 
	    float rangeperc=(bclip-wclip)/20.;
	    lbeg=wclip-rangeperc;
	  }
	  if (lendsup!=1) {
	    float rangeperc=(bclip-wclip)/20.;
	    lend=bclip+rangeperc;
	  }
	  
	  lfnum = lmin; getparfloat("lfnum",&lfnum);
	
	  getparstring("lstyle",&lstyles);
	  if (STREQ("vertright",lstyles))
	    lstyle = VERTRIGHT;
	  else if (STREQ("horibottom",lstyles))
	    lstyle = HORIBOTTOM;

	  /* legend dimensions (BEREND), Schoenfelder */
	  lwidth = 0.1 ;lheight = height/2;
	  if (lstyle==HORIBOTTOM) {
	    lwidth=width/1.2 ;lheight = 0.24;
	  }
	  getparfloat("lwidth",&lwidth);
	  getparfloat("lheight",&lheight);
	  
	  lx=.8;ly = ybox+(height-lheight)/2;
	  if (lstyle==VERTRIGHT) {
	    lx=xbox+width+0.1;
	  } else if (lstyle==HORIBOTTOM) {
	    lx=xbox+(width-lwidth)/2.0;ly = 1.0;
	  }
	  getparfloat("lx",&lx);
          if (lnice==1) lx = 8;   /* c liner */
	  getparfloat("ly",&ly);
	  
	  getparstring("lgrid",&lgrids);
	  if (STREQ("dot",lgrids))
	    ugrid = DOT;
	  else if (STREQ("dash",lgrids))
	    ugrid = DASH;
	  else if (STREQ("solid",lgrids))
	    ugrid = SOLID;
	  else
	    ugrid = NONE;
	}

	/* adjust x1beg and x1end to fall on sampled values */
	/* This will not allow to display an area greater than the data supplied */
	i1beg = NINT((x1beg-f1)/d1);
	i1beg = MAX(0,MIN(n1-1,i1beg));
	x1beg = f1+i1beg*d1;
	i1end = NINT((x1end-f1)/d1);
	i1end = MAX(0,MIN(n1-1,i1end));
	x1end = f1+i1end*d1;

	/* adjust x2beg and x2end to fall on sampled values */
	i2beg = NINT((x2beg-f2)/d2);
	i2beg = MAX(0,MIN(n2-1,i2beg));
	x2beg = f2+i2beg*d2;
	i2end = NINT((x2end-f2)/d2);
	i2end = MAX(0,MIN(n2-1,i2end));
	x2end = f2+i2end*d2;

	if (legend) {
	  /* Make legend color values */
	  int lll=0,lcount,perc5=13,ilbeg,ilend; /* color scale */
	  if (lbegsup!=1) {
	    ln+=perc5; /* white area */
	  }
	  if (lendsup!=1) {
	    ln+=perc5; /* black area */
	  }
	  data_legend = ealloc1(ln,sizeof(char));
	  if (lbegsup!=1) {
	    for (lll=0;lll<perc5;lll++) data_legend[lll]=(char) 255; /* white area */
	  }
	  for (lcount=255;lcount>=0;lcount--,lll++) data_legend[lll]=(char) lcount;
	  if (lendsup!=1) {
	    for (;lll<ln;lll++) data_legend[lll]=(char) 0; /* black area */
	  }
	  lf=lbeg;ld=(lend-lbeg)/(ln-1);
	  if (!(getparfloat("ldnum",&ldnum)))	ldnum=0.0;

	  /* adjust lbeg and lend to fall on sampled values */
	  ilbeg = NINT((lbeg-lf)/ld);
	  ilbeg = MAX(0,MIN(ln-1,ilbeg));
	  lbeg = lf+ilbeg*ld;
	  ilend = NINT((lend-lf)/ld);
	  ilend = MAX(0,MIN(ln-1,ilend));
	  lend = lf+ilend*ld;
	}
	/* allocate space for image bytes */
	n1c = 1+abs(i1end-i1beg);
	n2c = 1+abs(i2end-i2beg);
	cz = ealloc1(n1c*n2c,sizeof(char));

	/* convert data to be imaged into unsigned characters */
	zscale = (wclip!=bclip)?255.0/(wclip-bclip):1.0e10;
	zoffset = -bclip*zscale;
	i1step = (i1end>i1beg)?1:-1;
	i2step = (i2end>i2beg)?1:-1;
	czp = cz;
	for (i1c=0,i1=i1beg; i1c<n1c; i1c++,i1+=i1step) {
		for (i2c=0,i2=i2beg; i2c<n2c; i2c++,i2+=i2step) {
			zi = zoffset+z[i1+i2*n1]*zscale;
			if (zi<0.0) zi = 0.0;
			if (zi>255.0) zi = 255.0;
			*czp++ = (unsigned char)zi;
		}
	}
	free1float(z);

	/* determine sampling after scaling */
	n1s = MAX(1,NINT(1+(n1c-1)*d1/d1s));
	d1s = (n1s>1)?d1*(n1c-1)/(n1s-1):d1;
	n2s = MAX(1,NINT(1+(n2c-1)*d2/d2s));
	d2s = (n2s>1)?d2*(n2c-1)/(n2s-1):d2;

	/* if necessary, interpolate to scaled sampling intervals */
	if (n1s!=n1c || n2s!=n2c) {
		sz = ealloc1(n1s*n2s,sizeof(char));
		intl2b(n2c,d2,0.0,n1c,d1,0.0,cz,n2s,d2s,0.0,n1s,d1s,0.0,sz); /* Interpol array */
		free1(cz);
	} else {
		sz = cz;
	}

	/* determine axes pads */
	p1beg = (x1end>x1beg)?-fabs(d1s)/2:fabs(d1s)/2;
	p1end = (x1end>x1beg)?fabs(d1s)/2:-fabs(d1s)/2;
	p2beg = (x2end>x2beg)?-fabs(d2s)/2:fabs(d2s)/2;
	p2end = (x2end>x2beg)?fabs(d2s)/2:-fabs(d2s)/2;

	/* convert axes box parameters from inches to points */
	xbox *= 72.0;
	ybox *= 72.0;
	width *= 72.0;
	height *= 72.0;
	if (legend) {
	  lx *= 72.0; /* Schoenfelder */
	  ly *= 72.0; /* Schoenfelder */
	  lwidth *= 72.0; /* Schoenfelder */
	  lheight *= 72.0; /* Schoenfelder */
	}

	/* set bounding box */
	psAxesBBox(
		   xbox,ybox,width,height,
		   labelfont,labelsize,
		   titlefont,titlesize,
		   style,bbox);
	if (legend) {
	  psLegendBBox( /* Space for legend Schoenfelder */
			lx,ly,lwidth,lheight,
			labelfont,labelsize,
			lstyle,lbbox);
	  /* Include space for legend Schoenfelder */
	  bbox[0]=MIN(bbox[0],lbbox[0]);
	  bbox[1]=MIN(bbox[1],lbbox[1]);
	  bbox[2]=MAX(bbox[2],lbbox[2]);
	  bbox[3]=MAX(bbox[3],lbbox[3]);
	}
	boundingbox(bbox[0],bbox[1],bbox[2],bbox[3]);
	/* begin PostScript */
	begineps();

	/* save graphics state */
	gsave();

	/* translate coordinate system by box offset */
	translate(xbox,ybox);

	/* determine image matrix */
	if (style==NORMAL) {
		matrix[0] = 0;	matrix[1] = n1s;  matrix[2] = n2s;
		matrix[3] = 0;	matrix[4] = 0;	matrix[5] = 0;
	} else {
		matrix[0] = n2s;  matrix[1] = 0;  matrix[2] = 0;
		matrix[3] = -n1s;  matrix[4] = 0;  matrix[5] = n1s;
	}

	scale(width,height);

	/* draw the image (before axes so grid lines are visible) */
	drawimage(hls,colors,n2s,n1s,bps,matrix,sz);
	/***************************/
	/* main image has been drawn, restore graphics state */
	grestore();

	/* *********************************/
	/* draw the colorbar (before axes so grid lines are visible) Schoenfelder*/
	if (legend) {
	  gsave();
	  translate(lx,ly);
	  scale(lwidth,lheight);
	  if ((lstyle==VERTLEFT) || (lstyle==VERTRIGHT)) {
	    labmatrix[0] = 1;	 labmatrix[1] = 0;  labmatrix[2] = 0;
	    labmatrix[3] = ln; labmatrix[4] = 0;  labmatrix[5] = 0;
	    drawimage(hls,colors,1,ln,bps,labmatrix,data_legend);
	  } else {
	    labmatrix[0] = -1;	 labmatrix[1] = 0;  labmatrix[2] = 0;
	    labmatrix[3] = ln; labmatrix[4] = 0;  labmatrix[5] = 0;
	    rotate(-90);
	    drawimage(hls,colors,1,ln,bps,labmatrix,data_legend);
	    rotate(90);
	  }
	  
	  grestore();
	}

	/* draw curve */
	for (i=0; i<curve; i++) {
		gsave();
		psDrawCurve(
			xbox,ybox,width,height,
			x1beg,x1end,p1beg,p1end, 
			x2beg,x2end,p2beg,p2end,
			x1curve[i],x2curve[i],npair[i],
			curvecolor[i],curvewidth[i],curvedash[i],style);
		grestore();
	}


	gsave();
	/* draw axes and title */
	psAxesBox(
		  xbox,ybox,width,height,
		  x1beg,x1end,p1beg,p1end,
		  d1num,f1num,n1tic,grid1,label1,
		  x2beg,x2end,p2beg,p2end,
		  d2num,f2num,n2tic,grid2,label2,
		  labelfont,labelsize,
		  title,titlefont,titlesize,
		  titlecolor,axescolor,gridcolor,
		  ticwidth,axeswidth,gridwidth,
		  style);
	/* restore graphics state */
	grestore();

	/* draw axes and title for legend Schoenfelder*/
	if (legend) {
	  float lpbeg,lpend;
	  int lntic=1;
	  gsave();
	  lpbeg = 0.0; /*(lend>lbeg)?-fabs(d1s)/2:fabs(d1s)/2;*/
	  lpend = 0.0; /*(lend>lbeg)?fabs(d1s)/2:-fabs(d1s)/2;*/
	  
	  psLegendBox(
		    lx,ly,lwidth,lheight,
		    lbeg,lend,lpbeg,lpend,
		    ldnum,lf,lntic,ugrid,units,
		    labelfont,labelsize,
		    axescolor,gridcolor,
		    lstyle);
	  grestore();
	}

	/* end PostScript */
	showpage();
	endeps();

	if (curve) {
		free1int(npair);
		for (i=0; i<curve; i++) {
			free1float(x1curve[i]);
			free1float(x2curve[i]);
		}
		free1float(curvewidth);
		free1int(curvedash);
		free((void**)x1curve);
		free((void**)x2curve);
		free((void**)curvefile);
		free((void**)curvecolor);
	}

	return 0;
}