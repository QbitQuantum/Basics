void nb_kernel430_x86_64_sse2(int *           p_nri,
                              int *           iinr,
                              int *           jindex,
                              int *           jjnr,
                              int *           shift,
                              double *         shiftvec,
                              double *         fshift,
                              int *           gid,
                              double *         pos,
                              double *         faction,
                              double *         charge,
                              double *         p_facel,
                              double *         p_krf,
                              double *         p_crf,
                              double *         vc,
                              int *           type,
                              int *           p_ntype,
                              double *         vdwparam,
                              double *         vvdw,
                              double *         p_tabscale,
                              double *         VFtab,
                              double *         invsqrta,
                              double *         dvda,
                              double *         p_gbtabscale,
                              double *         GBtab,
                              int *           p_nthreads,
                              int *           count,
                              void *          mtx,
                              int *           outeriter,
                              int *           inneriter,
                              double *         work)
{
    int           nri,ntype,nthreads;
    int           n,ii,is3,ii3,k,nj0,nj1,ggid;
    double        shX,shY,shZ;
	int			  offset,nti;
    int           jnrA,jnrB;
    int           j3A,j3B;
	int           tjA,tjB;
	gmx_gbdata_t *gbdata;
	double *      gpol;
    
	__m128d  iq,qq,jq,isai;
	__m128d  ix,iy,iz;
	__m128d  jx,jy,jz;
	__m128d  dx,dy,dz;
	__m128d  vctot,vvdwtot,vgbtot,dvdasum,gbfactor;
	__m128d  fix,fiy,fiz,tx,ty,tz,rsq;
	__m128d  rinv,isaj,isaprod;
	__m128d  vcoul,fscal,gbscale,c6,c12;
	__m128d  rinvsq,r,rtab;
	__m128d  eps,Y,F,G,H;
    __m128d  VV,FF,Fp;
	__m128d  vgb,fijGB,dvdatmp;
	__m128d  rinvsix,vvdw6,vvdw12,vvdwtmp;
	__m128d  facel,gbtabscale,dvdaj;
    __m128d  fijD,fijR;
    __m128d  xmm1,tabscale,eps2;
	__m128i  n0, nnn;
    
	
	const __m128d neg        = _mm_set1_pd(-1.0);
	const __m128d zero       = _mm_set1_pd(0.0);
	const __m128d minushalf  = _mm_set1_pd(-0.5);
	const __m128d two        = _mm_set1_pd(2.0);
	
	gbdata     = (gmx_gbdata_t *)work;
	gpol       = gbdata->gpol;
    
	nri        = *p_nri;
	ntype      = *p_ntype;
    
    gbfactor   = _mm_set1_pd( - ((1.0/gbdata->epsilon_r) - (1.0/gbdata->gb_epsilon_solvent)));     
    gbtabscale = _mm_load1_pd(p_gbtabscale);  
    facel      = _mm_load1_pd(p_facel);
    tabscale   = _mm_load1_pd(p_tabscale);
    
    nj1         = 0;
    jnrA = jnrB = 0;
    j3A = j3B   = 0;
    jx          = _mm_setzero_pd();
    jy          = _mm_setzero_pd();
    jz          = _mm_setzero_pd();
    c6          = _mm_setzero_pd();
    c12         = _mm_setzero_pd();
	
	for(n=0;n<nri;n++)
	{
        is3              = 3*shift[n];     
        shX              = shiftvec[is3];  
        shY              = shiftvec[is3+1];
        shZ              = shiftvec[is3+2];
        nj0              = jindex[n];      
        nj1              = jindex[n+1];    
        ii               = iinr[n];        
        ii3              = 3*ii;           
		
		ix               = _mm_set1_pd(shX+pos[ii3+0]);
		iy               = _mm_set1_pd(shY+pos[ii3+1]);
		iz               = _mm_set1_pd(shZ+pos[ii3+2]);
        
		iq               = _mm_load1_pd(charge+ii);
		iq               = _mm_mul_pd(iq,facel);
        
		isai             = _mm_load1_pd(invsqrta+ii);
        
		nti              = 2*ntype*type[ii];
		
		vctot            = _mm_setzero_pd();
		vvdwtot          = _mm_setzero_pd();
		vgbtot           = _mm_setzero_pd();
		dvdasum          = _mm_setzero_pd();
		fix              = _mm_setzero_pd();
		fiy              = _mm_setzero_pd();
		fiz              = _mm_setzero_pd();
        
		for(k=nj0;k<nj1-1; k+=2)
		{
			jnrA    = jjnr[k];
			jnrB    = jjnr[k+1];
			
			j3A     = jnrA * 3;
			j3B     = jnrB * 3;
            
            GMX_MM_LOAD_1RVEC_2POINTERS_PD(pos+j3A,pos+j3B,jx,jy,jz);
            
			dx           = _mm_sub_pd(ix,jx);
			dy           = _mm_sub_pd(iy,jy);
			dz           = _mm_sub_pd(iz,jz);
            
            rsq          = gmx_mm_calc_rsq_pd(dx,dy,dz);
            
            rinv         = gmx_mm_invsqrt_pd(rsq);
 			rinvsq       = _mm_mul_pd(rinv,rinv);
            
			/***********************************/
			/* INTERACTION SECTION STARTS HERE */
			/***********************************/
			GMX_MM_LOAD_2VALUES_PD(charge+jnrA,charge+jnrB,jq);
			GMX_MM_LOAD_2VALUES_PD(invsqrta+jnrA,invsqrta+jnrB,isaj);
            
            /* Lennard-Jones */
            tjA          = nti+2*type[jnrA];
			tjB          = nti+2*type[jnrB];
            
            GMX_MM_LOAD_2PAIRS_PD(vdwparam+tjA,vdwparam+tjB,c6,c12);
			
			isaprod      = _mm_mul_pd(isai,isaj);
			qq           = _mm_mul_pd(iq,jq);            
			vcoul        = _mm_mul_pd(qq,rinv);
			fscal        = _mm_mul_pd(vcoul,rinv);                                 
            vctot        = _mm_add_pd(vctot,vcoul);
            
            /* Polarization interaction */
			qq           = _mm_mul_pd(qq,_mm_mul_pd(isaprod,gbfactor));
			gbscale      = _mm_mul_pd(isaprod,gbtabscale);
            
 			/* Calculate GB table index */
			r            = _mm_mul_pd(rsq,rinv);
			rtab         = _mm_mul_pd(r,gbscale);
			
			n0		     = _mm_cvttpd_epi32(rtab);
			eps	     	 = _mm_sub_pd(rtab,_mm_cvtepi32_pd(n0));
			nnn		     = _mm_slli_epi32(n0,2);
			
            /* the tables are 16-byte aligned, so we can use _mm_load_pd */			
            Y            = _mm_load_pd(GBtab+(gmx_mm_extract_epi32(nnn,0))); 
            F            = _mm_load_pd(GBtab+(gmx_mm_extract_epi32(nnn,1)));
            GMX_MM_TRANSPOSE2_PD(Y,F);
            G            = _mm_load_pd(GBtab+(gmx_mm_extract_epi32(nnn,0))+2); 
            H            = _mm_load_pd(GBtab+(gmx_mm_extract_epi32(nnn,1))+2);
            GMX_MM_TRANSPOSE2_PD(G,H);
            
            G       = _mm_mul_pd(G,eps);
            H       = _mm_mul_pd(H, _mm_mul_pd(eps,eps) );
            F       = _mm_add_pd(F, _mm_add_pd( G , H ) );
            Y       = _mm_add_pd(Y, _mm_mul_pd(F, eps));
            F       = _mm_add_pd(F, _mm_add_pd(G , _mm_mul_pd(H,two)));
            vgb     = _mm_mul_pd(Y, qq);           
            fijGB   = _mm_mul_pd(F, _mm_mul_pd(qq,gbscale));
            
            dvdatmp = _mm_mul_pd(_mm_add_pd(vgb, _mm_mul_pd(fijGB,r)) , minushalf);
            
            vgbtot  = _mm_add_pd(vgbtot, vgb);
            
            dvdasum = _mm_add_pd(dvdasum, dvdatmp);
            dvdatmp = _mm_mul_pd(dvdatmp, _mm_mul_pd(isaj,isaj));
            
            GMX_MM_INCREMENT_2VALUES_PD(dvda+jnrA,dvda+jnrB,dvdatmp);
			
            /* Calculate VDW table index */
			rtab    = _mm_mul_pd(r,tabscale);
			n0      = _mm_cvttpd_epi32(rtab);
			eps     = _mm_sub_pd(rtab,_mm_cvtepi32_pd(n0));
			eps2    = _mm_mul_pd(eps,eps);
			nnn     = _mm_slli_epi32(n0,3);
			
            /* Dispersion */
            Y            = _mm_load_pd(VFtab+(gmx_mm_extract_epi32(nnn,0))); 
            F            = _mm_load_pd(VFtab+(gmx_mm_extract_epi32(nnn,1)));
            GMX_MM_TRANSPOSE2_PD(Y,F);
            G            = _mm_load_pd(VFtab+(gmx_mm_extract_epi32(nnn,0))+2); 
            H            = _mm_load_pd(VFtab+(gmx_mm_extract_epi32(nnn,1))+2);
            GMX_MM_TRANSPOSE2_PD(G,H);
            
            G       = _mm_mul_pd(G,eps);
			H       = _mm_mul_pd(H,eps2);
			Fp      = _mm_add_pd(F,G);
			Fp      = _mm_add_pd(Fp,H);
			VV      = _mm_mul_pd(Fp,eps);
			VV      = _mm_add_pd(Y,VV);
			xmm1    = _mm_mul_pd(two,H);
			FF      = _mm_add_pd(Fp,G);
			FF      = _mm_add_pd(FF,xmm1);
			
			vvdw6   = _mm_mul_pd(c6,VV);
			fijD    = _mm_mul_pd(c6,FF);
            
            /* Dispersion */
            Y            = _mm_load_pd(VFtab+(gmx_mm_extract_epi32(nnn,0))+4); 
            F            = _mm_load_pd(VFtab+(gmx_mm_extract_epi32(nnn,1))+4);
            GMX_MM_TRANSPOSE2_PD(Y,F);
            G            = _mm_load_pd(VFtab+(gmx_mm_extract_epi32(nnn,0))+6); 
            H            = _mm_load_pd(VFtab+(gmx_mm_extract_epi32(nnn,1))+6);
            GMX_MM_TRANSPOSE2_PD(G,H);
            
            G       = _mm_mul_pd(G,eps);
			H       = _mm_mul_pd(H,eps2);
			Fp      = _mm_add_pd(F,G);
			Fp      = _mm_add_pd(Fp,H);
			VV      = _mm_mul_pd(Fp,eps);
			VV      = _mm_add_pd(Y,VV);
			xmm1    = _mm_mul_pd(two,H);
			FF      = _mm_add_pd(Fp,G);
			FF      = _mm_add_pd(FF,xmm1);
			
			vvdw12  = _mm_mul_pd(c12,VV);
			fijR    = _mm_mul_pd(c12,FF);
			
			vvdwtmp = _mm_add_pd(vvdw12,vvdw6);
			vvdwtot = _mm_add_pd(vvdwtot,vvdwtmp);
            
			xmm1    = _mm_add_pd(fijD,fijR);
			xmm1    = _mm_mul_pd(xmm1,tabscale);
			xmm1    = _mm_add_pd(xmm1,fijGB);
			xmm1    = _mm_sub_pd(xmm1,fscal);
			fscal   = _mm_mul_pd(xmm1,neg);
			fscal   = _mm_mul_pd(fscal,rinv);
            
            /***********************************/
			/*  INTERACTION SECTION ENDS HERE  */
			/***********************************/
            
            /* Calculate temporary vectorial force */
            tx           = _mm_mul_pd(fscal,dx);
            ty           = _mm_mul_pd(fscal,dy);
            tz           = _mm_mul_pd(fscal,dz);
            
            /* Increment i atom force */
            fix          = _mm_add_pd(fix,tx);
            fiy          = _mm_add_pd(fiy,ty);
            fiz          = _mm_add_pd(fiz,tz);
            
            /* Store j forces back */
			GMX_MM_DECREMENT_1RVEC_2POINTERS_PD(faction+j3A,faction+j3B,tx,ty,tz);
		}
		
		/* In double precision, offset can only be either 0 or 1 */
		if(k<nj1)
		{
			jnrA    = jjnr[k];
			j3A     = jnrA * 3;
            
            GMX_MM_LOAD_1RVEC_1POINTER_PD(pos+j3A,jx,jy,jz);
            
			dx           = _mm_sub_sd(ix,jx);
			dy           = _mm_sub_sd(iy,jy);
			dz           = _mm_sub_sd(iz,jz);
            
            rsq          = gmx_mm_calc_rsq_pd(dx,dy,dz);
            
            rinv         = gmx_mm_invsqrt_pd(rsq);
 			rinvsq       = _mm_mul_sd(rinv,rinv);
            
			/***********************************/
			/* INTERACTION SECTION STARTS HERE */
			/***********************************/
			GMX_MM_LOAD_1VALUE_PD(charge+jnrA,jq);
			GMX_MM_LOAD_1VALUE_PD(invsqrta+jnrA,isaj);
            
            /* Lennard-Jones */
            tjA          = nti+2*type[jnrA];
            
            GMX_MM_LOAD_1PAIR_PD(vdwparam+tjA,c6,c12);
			
			isaprod      = _mm_mul_sd(isai,isaj);
			qq           = _mm_mul_sd(iq,jq);            
			vcoul        = _mm_mul_sd(qq,rinv);
			fscal        = _mm_mul_sd(vcoul,rinv);                                 
            vctot        = _mm_add_sd(vctot,vcoul);
            
            /* Polarization interaction */
			qq           = _mm_mul_sd(qq,_mm_mul_sd(isaprod,gbfactor));
			gbscale      = _mm_mul_sd(isaprod,gbtabscale);
            
 			/* Calculate GB table index */
			r            = _mm_mul_sd(rsq,rinv);
			rtab         = _mm_mul_sd(r,gbscale);
			
			n0		     = _mm_cvttpd_epi32(rtab);
			eps	     	 = _mm_sub_sd(rtab,_mm_cvtepi32_pd(n0));
			nnn		     = _mm_slli_epi32(n0,2);
			
            /* the tables are 16-byte aligned, so we can use _mm_load_pd */			
            Y            = _mm_load_pd(GBtab+(gmx_mm_extract_epi32(nnn,0))); 
            F            = _mm_setzero_pd();
            GMX_MM_TRANSPOSE2_PD(Y,F);
            G            = _mm_load_pd(GBtab+(gmx_mm_extract_epi32(nnn,0))+2); 
            H            = _mm_setzero_pd();
            GMX_MM_TRANSPOSE2_PD(G,H);
            
            G       = _mm_mul_sd(G,eps);
            H       = _mm_mul_sd(H, _mm_mul_sd(eps,eps) );
            F       = _mm_add_sd(F, _mm_add_sd( G , H ) );
            Y       = _mm_add_sd(Y, _mm_mul_sd(F, eps));
            F       = _mm_add_sd(F, _mm_add_sd(G , _mm_mul_sd(H,two)));
            vgb     = _mm_mul_sd(Y, qq);           
            fijGB   = _mm_mul_sd(F, _mm_mul_sd(qq,gbscale));
            
            dvdatmp = _mm_mul_sd(_mm_add_sd(vgb, _mm_mul_sd(fijGB,r)) , minushalf);
            
            vgbtot  = _mm_add_sd(vgbtot, vgb);
            
            dvdasum = _mm_add_sd(dvdasum, dvdatmp);
            dvdatmp = _mm_mul_sd(dvdatmp, _mm_mul_sd(isaj,isaj));
            
            GMX_MM_INCREMENT_1VALUE_PD(dvda+jnrA,dvdatmp);
			
            /* Calculate VDW table index */
			rtab    = _mm_mul_sd(r,tabscale);
			n0      = _mm_cvttpd_epi32(rtab);
			eps     = _mm_sub_sd(rtab,_mm_cvtepi32_pd(n0));
			eps2    = _mm_mul_sd(eps,eps);
			nnn     = _mm_slli_epi32(n0,3);
			
            /* Dispersion */
            Y            = _mm_load_pd(VFtab+(gmx_mm_extract_epi32(nnn,0))); 
            F            = _mm_setzero_pd();
            GMX_MM_TRANSPOSE2_PD(Y,F);
            G            = _mm_load_pd(VFtab+(gmx_mm_extract_epi32(nnn,0))+2); 
            H            = _mm_setzero_pd();
            GMX_MM_TRANSPOSE2_PD(G,H);
            
            G       = _mm_mul_sd(G,eps);
			H       = _mm_mul_sd(H,eps2);
			Fp      = _mm_add_sd(F,G);
			Fp      = _mm_add_sd(Fp,H);
			VV      = _mm_mul_sd(Fp,eps);
			VV      = _mm_add_sd(Y,VV);
			xmm1    = _mm_mul_sd(two,H);
			FF      = _mm_add_sd(Fp,G);
			FF      = _mm_add_sd(FF,xmm1);
			
			vvdw6   = _mm_mul_sd(c6,VV);
			fijD    = _mm_mul_sd(c6,FF);
            
            /* Dispersion */
            Y            = _mm_load_pd(VFtab+(gmx_mm_extract_epi32(nnn,0))+4); 
            F            = _mm_setzero_pd();
            GMX_MM_TRANSPOSE2_PD(Y,F);
            G            = _mm_load_pd(VFtab+(gmx_mm_extract_epi32(nnn,0))+6); 
            H            = _mm_setzero_pd();
            GMX_MM_TRANSPOSE2_PD(G,H);
            
            G       = _mm_mul_sd(G,eps);
			H       = _mm_mul_sd(H,eps2);
			Fp      = _mm_add_sd(F,G);
			Fp      = _mm_add_sd(Fp,H);
			VV      = _mm_mul_sd(Fp,eps);
			VV      = _mm_add_sd(Y,VV);
			xmm1    = _mm_mul_sd(two,H);
			FF      = _mm_add_sd(Fp,G);
			FF      = _mm_add_sd(FF,xmm1);
			
			vvdw12  = _mm_mul_sd(c12,VV);
			fijR    = _mm_mul_sd(c12,FF);
			
			vvdwtmp = _mm_add_sd(vvdw12,vvdw6);
			vvdwtot = _mm_add_sd(vvdwtot,vvdwtmp);
            
			xmm1    = _mm_add_sd(fijD,fijR);
			xmm1    = _mm_mul_sd(xmm1,tabscale);
			xmm1    = _mm_add_sd(xmm1,fijGB);
			xmm1    = _mm_sub_sd(xmm1,fscal);
			fscal   = _mm_mul_sd(xmm1,neg);
			fscal   = _mm_mul_sd(fscal,rinv);

            /***********************************/
			/*  INTERACTION SECTION ENDS HERE  */
			/***********************************/
            
            /* Calculate temporary vectorial force */
            tx           = _mm_mul_sd(fscal,dx);
            ty           = _mm_mul_sd(fscal,dy);
            tz           = _mm_mul_sd(fscal,dz);
            
            /* Increment i atom force */
            fix          = _mm_add_sd(fix,tx);
            fiy          = _mm_add_sd(fiy,ty);
            fiz          = _mm_add_sd(fiz,tz);
            
            /* Store j forces back */
			GMX_MM_DECREMENT_1RVEC_1POINTER_PD(faction+j3A,tx,ty,tz);
		}
		
        dvdasum = _mm_mul_pd(dvdasum, _mm_mul_pd(isai,isai));
        gmx_mm_update_iforce_1atom_pd(&fix,&fiy,&fiz,faction+ii3,fshift+is3);
        
        ggid     = gid[n];         
        
        gmx_mm_update_2pot_pd(vctot,vc+ggid,vvdwtot,vvdw+ggid);
        gmx_mm_update_2pot_pd(vgbtot,gpol+ggid,dvdasum,dvda+ii);
	}
    
	*outeriter   = nri;            
    *inneriter   = nj1; 	
}