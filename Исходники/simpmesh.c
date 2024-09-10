float mc_next_scatter(float g, float3 *dir,RandType *ran, RandType *ran0, mcconfig *cfg, float *pmom){

    float nextslen;
    float sphi,cphi,tmp0,theta,stheta,ctheta,tmp1;
    float3 p;

    rand_need_more(ran,ran0);

    //random scattering length (normalized)
#ifdef MMC_USE_SSE_MATH
    nextslen=rand_next_scatlen_ps(ran);
#else
    nextslen=rand_next_scatlen(ran);
#endif

    //random arimuthal angle
#ifdef MMC_USE_SSE_MATH
    rand_next_aangle_sincos(ran,&sphi,&cphi);
#else
    tmp0=TWO_PI*rand_next_aangle(ran); //next arimuth angle
    mmc_sincosf(tmp0,&sphi,&cphi);
#endif

    //Henyey-Greenstein Phase Function, "Handbook of Optical Biomedical Diagnostics",2002,Chap3,p234
    //see Boas2002

    if(g>EPS){  //if g is too small, the distribution of theta is bad
	tmp0=(1.f-g*g)/(1.f-g+2.f*g*rand_next_zangle(ran));
	tmp0*=tmp0;
	tmp0=(1.f+g*g-tmp0)/(2.f*g);

    	// when ran=1, CUDA will give me 1.000002 for tmp0 which produces nan later
    	if(tmp0> 1.f) tmp0=1.f;
        if(tmp0<-1.f) tmp0=-1.f;

	theta=acosf(tmp0);
	stheta=sqrt(1.f-tmp0*tmp0);
	//stheta=sinf(theta);
	ctheta=tmp0;
    }else{
	theta=acosf(2.f*rand_next_zangle(ran)-1.f);
    	mmc_sincosf(theta,&stheta,&ctheta);
    }

    if( dir->z>-1.f+EPS && dir->z<1.f-EPS ) {
	tmp0=1.f-dir->z*dir->z;   //reuse tmp to minimize registers
	tmp1=1.f/sqrtf(tmp0);
	tmp1=stheta*tmp1;

	p.x=tmp1*(dir->x*dir->z*cphi - dir->y*sphi) + dir->x*ctheta;
	p.y=tmp1*(dir->y*dir->z*cphi + dir->x*sphi) + dir->y*ctheta;
	p.z=-tmp1*tmp0*cphi			    + dir->z*ctheta;
    }else{
	p.x=stheta*cphi;
	p.y=stheta*sphi;
	p.z=(dir->z>0.f)?ctheta:-ctheta;
    }
    if (cfg->ismomentum)
        pmom[0]+=(1.f-ctheta);

    dir->x=p.x;
    dir->y=p.y;
    dir->z=p.z;
    return nextslen;
}