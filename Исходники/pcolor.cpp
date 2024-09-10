    void draw_quad(int qi, int qj,
		   vector<int>& imin, vector<int>& imax
	) {
	int i,j;
	double u, v;
	double v0, v1, v2, v3, v4;
	// Coordonnees du quad dans l'offscreen
	double ax = (X.value(qj+0,qi+0)-x1)*m_dx, ay=(Y.value(qj+0,qi+0)-y1)*m_dy;
	double bx = (X.value(qj+0,qi+1)-x1)*m_dx, by=(Y.value(qj+0,qi+1)-y1)*m_dy;
	double cx = (X.value(qj+1,qi+1)-x1)*m_dx, cy=(Y.value(qj+1,qi+1)-y1)*m_dy;
	double dx = (X.value(qj+1,qi+0)-x1)*m_dx, dy=(Y.value(qj+1,qi+0)-y1)*m_dy;
	// indice des sommets (A,B,C,D)<->0,1,2,3<->(qi,qj),(qi+1,qj),(qi+1,qj+1),(qi,qj+1)
	// trie par ordre x croissant ou y croissant (selon xarg, yarg)
	double ymin = min(ay,min(by,min(cy,dy)));
	double ymax = max(ay,max(by,max(cy,dy)));

	int i0 = int(ymin+.5);
	int i1 = int(ymax+.5);
//	printf("Quads: i=%d->%d\n", i0, i1);

	if (i0<0) i0=0;
	if (i1>=D.ni) i1=D.ni-1;
	if (i1<i0) return;

	iymin = min(iymin,i0);
	iymax = max(iymax,i1);
	for(i=i0;i<=i1;++i) {
	    imax[i]=-1;
	    imin[i]=D.nj;
	}

	// Compute the rasterized border of the quad
	bool visible = false;
	visible |= vert_line(ax,ay,bx,by,D.nj,imin,imax, border, 0xff000000, D);
	visible |= vert_line(bx,by,cx,cy,D.nj,imin,imax, border, 0xff000000, D);
	visible |= vert_line(cx,cy,dx,dy,D.nj,imin,imax, border, 0xff000000, D);
	visible |= vert_line(dx,dy,ax,ay,D.nj,imin,imax, border, 0xff000000, D);
	if (!visible)
	    return;

	double ex = ax+cx-dx-bx;
	double ey = ay+cy-dy-by;
	double n = 1./sqrt((cx-ax)*(cx-ax)+(cy-ay)*(cy-ay));
	if (n>1e2) n = 1.0;

	// Normalize vectors with ||AC||
	ax *= n; ay *= n;
	bx = bx*n-ax; by = by*n-ay;
	cx = cx*n-ax; cy = cy*n-ay;
	dx = dx*n-ax; dy = dy*n-ay;
	ex *= n; ey *= n;

	v1 = Z.value(qj,qi);
	v2 = Z.value(qj+1,qi);
	v3 = Z.value(qj+1,qi+1);
	v4 = Z.value(qj,qi+1);

	if (isnan(v1) || isnan(v2) || isnan(v3) || isnan(v4)) {
	    // XXX Color = Alpha
	    return ;
	}
	int dm=0, dM=0;
	if (border) {
	    dm=1;dM=-1;
	}
	npy_uint32 col = scale.eval( v1*(1-vflat)*(1-uflat) +
				 v2*  vflat  *(1-uflat) +
				 v3*  vflat  *  uflat   +
				 v4*(1-vflat)*  uflat   );
	for(i=i0+dm;i<=i1+dM;++i) {
	    ixmin = min(ixmin,imin[i]);
	    ixmax = max(ixmax,imax[i]);
	    int jmin=max(0,imin[i])+dm;
	    int jmax=min(imax[i],D.nj-1)+dM;
	    for(j=jmin;j<=jmax;++j) {
		if (!flat) {
		    params(j*n,i*n, ax,ay, bx,by, cx,cy, dx,dy, ex,ey, u,v);
		    if (u<0) u=0.; else if (u>1.) u=1.;
		    if (v<0) v=0.; else if (v>1.) v=1.;
		    /* v0 = v1*(1-v)*(1-u) + v2*v*(1-u) + v3*v*u + v4*(1-v)*u; */
		    v0 = u*( v*(v1-v2+v3-v4)+v4-v1 ) + v*(v2-v1) + v1;
		    col = scale.eval(v0);
		}
		D.value(j,i) = col;
	    }
	}
    }