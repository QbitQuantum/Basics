//-----------------------------------------------------------------------------
//
//	Surf3C series
//
//-----------------------------------------------------------------------------
void mglGraph::Surf3C(mreal val, const mglData &x, const mglData &y, const mglData &z, const mglData &a, const mglData &b, const char *sch)
{
	long i,j,k,i0,i1,n=a.nx,m=a.ny,l=a.nz;
	long *kx1,*kx2,*ky1,*ky2,*kz,pc;
	bool both, wire = sch && strchr(sch,'#');
	mreal *pp=0,*cc=0,*kk=0,*nn=0;
	mreal d,xx,yy,zz,nx,ny,nz,dx,dy,dz,tx,ty,tz,alpha;
	if(n<2 || m<2 || l<2)	{	SetWarn(mglWarnLow,"Surf3C");	return;	}
	both = x.nx*x.ny*x.nz==n*m*l && y.nx*y.ny*y.nz==n*m*l && z.nx*z.ny*z.nz==n*m*l;
	if(!(both || (x.nx==n && y.nx==m && z.nx==l)))
	{	SetWarn(mglWarnDim,"Surf3C");	return;	}
	if(b.nx*b.ny*b.nz!=n*m*l)	{	SetWarn(mglWarnDim,"Surf3C");	return;	}
	static int cgid=1;	StartGroup("Surf3C",cgid++);

	bool inv = (sch && strchr(sch,'-'));
	SetScheme(sch);
	kx1 = new long[n*m];	kx2 = new long[n*m];
	ky1 = new long[n*m];	ky2 = new long[n*m];
	kz  = new long[n*m];
	Pal[100]=GetC(val);
//	DefColor(c,AlphaDef);

	for(k=0;k<l;k++)
	{
		memcpy(kx1,kx2,n*m*sizeof(long));	memset(kx2,-1,n*m*sizeof(long));
		memcpy(ky1,ky2,n*m*sizeof(long));	memset(ky2,-1,n*m*sizeof(long));
		memset(kz ,-1,n*m*sizeof(long));
		for(i=0;i<n;i++)	for(j=0;j<m;j++)
		{
			i1 = i+n*j;	i0 = i1+n*m*k;
			if(i<n-1)
			{
				d = _d(val,a.a[i0],a.a[i0+1]);
				if(d>=0 && d<1)
				{
					xx = both ? x.a[i0]*(1.-d)+x.a[i0+1]*d : x.a[i]*(1.-d)+x.a[i+1]*d;
					yy = both ? y.a[i0]*(1.-d)+y.a[i0+1]*d : y.a[j];
					zz = both ? z.a[i0]*(1.-d)+z.a[i0+1]*d : z.a[k];
					alpha = b.a[i0]*(1.-d)+b.a[i0+1]*d;
					normal_3d(a,i+d,j,k,&dx,&dy,&dz,inv);
					if(both)
					{
						normal_3d(x,i+d,j,k,&tx,&ty,&tz,true);
						nx = (dx*tx+dy*ty+dz*tz)/(tx*tx+ty*ty+tz*tz);
						normal_3d(y,i+d,j,k,&tx,&ty,&tz,true);
						ny = (dx*tx+dy*ty+dz*tz)/(tx*tx+ty*ty+tz*tz);
						normal_3d(z,i+d,j,k,&tx,&ty,&tz,true);
						nz = (dx*tx+dy*ty+dz*tz)/(tx*tx+ty*ty+tz*tz);
					}
					else
					{
						normal_1d(x,i+d,&tx,true);		nx = dx/tx;
						normal_1d(y,j,&ty,true);		ny = dy/ty;
						normal_1d(z,k,&tz,true);		nz = dz/tz;
					}
					Pal[100]=GetC(alpha);
					kx2[i1] = add_spoint(pc,&pp,&kk,&cc,&nn,xx,yy,zz,nx,ny,nz,
							i+d,j,k,Transparent ? AlphaDef : 1);
				}
			}
			if(j<m-1)
			{
				d = _d(val,a.a[i0],a.a[i0+n]);
				if(d>=0 && d<1)
				{
					xx = both ? x.a[i0]*(1.-d)+x.a[i0+n]*d : x.a[i];
					yy = both ? y.a[i0]*(1.-d)+y.a[i0+n]*d : y.a[j]*(1.-d)+y.a[j+1]*d;
					zz = both ? z.a[i0]*(1.-d)+z.a[i0+n]*d : z.a[k];
					alpha = b.a[i0]*(1.-d)+b.a[i0+n]*d;
					normal_3d(a,i,j+d,k,&dx,&dy,&dz,inv);
					if(both)
					{
						normal_3d(x,i,j+d,k,&tx,&ty,&tz,true);
						nx = (dx*tx+dy*ty+dz*tz)/(tx*tx+ty*ty+tz*tz);
						normal_3d(y,i,j+d,k,&tx,&ty,&tz,true);
						ny = (dx*tx+dy*ty+dz*tz)/(tx*tx+ty*ty+tz*tz);
						normal_3d(z,i,j+d,k,&tx,&ty,&tz,true);
						nz = (dx*tx+dy*ty+dz*tz)/(tx*tx+ty*ty+tz*tz);
					}
					else
					{
						normal_1d(x,i,&tx,true);		nx = dx/tx;
						normal_1d(y,j+d,&ty,true);		ny = dy/ty;
						normal_1d(z,k,&tz,true);		nz = dz/tz;
					}
					Pal[100]=GetC(alpha);
					ky2[i1] = add_spoint(pc,&pp,&kk,&cc,&nn,xx,yy,zz,nx,ny,nz,
							i,j+d,k,Transparent ? AlphaDef : 1);
				}
			}
			if(k>0)
			{
				d = _d(val,a.a[i0-n*m],a.a[i0]);
				if(d>=0 && d<1)
				{
					xx = both ? x.a[i0-n*m]*(1.-d)+x.a[i0]*d : x.a[i];
					yy = both ? y.a[i0-n*m]*(1.-d)+y.a[i0]*d : y.a[j];
					zz = both ? z.a[i0-n*m]*(1.-d)+z.a[i0]*d : z.a[k-1]*(1.-d)+z.a[k]*d;
					alpha = b.a[i0-n*m]*(1.-d)+b.a[i0]*d;
					normal_3d(a,i,j,k+d-1,&dx,&dy,&dz,inv);
					if(both)
					{
						normal_3d(x,i,j,k+d-1,&tx,&ty,&tz,true);
						nx = (dx*tx+dy*ty+dz*tz)/(tx*tx+ty*ty+tz*tz);
						normal_3d(y,i,j,k+d-1,&tx,&ty,&tz,true);
						ny = (dx*tx+dy*ty+dz*tz)/(tx*tx+ty*ty+tz*tz);
						normal_3d(z,i,j,k+d-1,&tx,&ty,&tz,true);
						nz = (dx*tx+dy*ty+dz*tz)/(tx*tx+ty*ty+tz*tz);
					}
					else
					{
						normal_1d(x,i,&tx,true);		nx = dx/tx;
						normal_1d(y,j,&ty,true);		ny = dy/ty;
						normal_1d(z,k+d-1,&tz,true);	nz = dz/tz;
					}
					Pal[100]=GetC(alpha);
					kz[i1] = add_spoint(pc,&pp,&kk,&cc,&nn,xx,yy,zz,nx,ny,nz,
							i,j,k+d-1,Transparent ? AlphaDef : 1);
				}
			}
		}
		if(k>0)	surf3_plot(n,m,kx1,kx2,ky1,ky2,kz,pp,cc,kk,nn,wire);
	}
	EndGroup();
	delete []kx1;	delete []kx2;	delete []ky1;	delete []ky2;	delete []kz;
	if(pp)	{	free(pp);	free(kk);	free(cc);	free(nn);	}
}