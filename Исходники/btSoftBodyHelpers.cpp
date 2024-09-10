btSoftBody*		btSoftBodyHelpers::CreatePatch(btSoftBodyWorldInfo& worldInfo,const btVector3& corner00,
											   const btVector3& corner10,
											   const btVector3& corner01,
											   const btVector3& corner11,
											   int resx,
											   int resy,
											   int fixeds,
											   bool gendiags)
{
#define IDX(_x_,_y_)	((_y_)*rx+(_x_))
	/* Create nodes	*/ 
	if((resx<2)||(resy<2)) return(0);
	const int	rx=resx;
	const int	ry=resy;
	const int	tot=rx*ry;
	btVector3*	x=new btVector3[tot];
	btScalar*	m=new btScalar[tot];
	int iy;

	for(iy=0;iy<ry;++iy)
	{
		const btScalar	ty=iy/(btScalar)(ry-1);
		const btVector3	py0=lerp(corner00,corner01,ty);
		const btVector3	py1=lerp(corner10,corner11,ty);
		for(int ix=0;ix<rx;++ix)
		{
			const btScalar	tx=ix/(btScalar)(rx-1);
			x[IDX(ix,iy)]=lerp(py0,py1,tx);
			m[IDX(ix,iy)]=1;
		}
	}
	btSoftBody*		psb=new btSoftBody(&worldInfo,tot,x,m);
	if(fixeds&1)	psb->setMass(IDX(0,0),0);
	if(fixeds&2)	psb->setMass(IDX(rx-1,0),0);
	if(fixeds&4)	psb->setMass(IDX(0,ry-1),0);
	if(fixeds&8)	psb->setMass(IDX(rx-1,ry-1),0);
	delete[] x;
	delete[] m;
	/* Create links	and faces */ 
	for(iy=0;iy<ry;++iy)
	{
		for(int ix=0;ix<rx;++ix)
		{
			const int	idx=IDX(ix,iy);
			const bool	mdx=(ix+1)<rx;
			const bool	mdy=(iy+1)<ry;
			if(mdx) psb->appendLink(idx,IDX(ix+1,iy));
			if(mdy) psb->appendLink(idx,IDX(ix,iy+1));
			if(mdx&&mdy)
			{
				if((ix+iy)&1)
				{
					psb->appendFace(IDX(ix,iy),IDX(ix+1,iy),IDX(ix+1,iy+1));
					psb->appendFace(IDX(ix,iy),IDX(ix+1,iy+1),IDX(ix,iy+1));
					if(gendiags)
					{
						psb->appendLink(IDX(ix,iy),IDX(ix+1,iy+1));
					}
				}
				else
				{
					psb->appendFace(IDX(ix,iy+1),IDX(ix,iy),IDX(ix+1,iy));
					psb->appendFace(IDX(ix,iy+1),IDX(ix+1,iy),IDX(ix+1,iy+1));
					if(gendiags)
					{
						psb->appendLink(IDX(ix+1,iy),IDX(ix,iy+1));
					}
				}
			}
		}
	}
	/* Finished		*/ 
#undef IDX
	return(psb);
}