int 
calc_gb_rad_hct_obc_sse2_double(t_commrec *cr, t_forcerec * fr, int natoms, gmx_localtop_t *top,
                                const t_atomtypes *atype, double *x, t_nblist *nl, gmx_genborn_t *born,t_mdatoms *md,int gb_algorithm)
{
	int i,ai,k,n,ii,ii3,is3,nj0,nj1,at0,at1,offset;
    int jnrA,jnrB;
    int j3A,j3B;
	double shX,shY,shZ;
	double rr,rr_inv,rr_inv2,sum_tmp,sum,sum2,sum3,gbr;
	double sum_ai2, sum_ai3,tsum,tchain,doffset;
	double *obc_param;
    double *gb_radius;
    double *work;
    int *  jjnr;
    double *dadx;
    double *shiftvec;
    double min_rad,rad;
    
	__m128d ix,iy,iz,jx,jy,jz;
	__m128d dx,dy,dz,t1,t2,t3,t4;
	__m128d rsq,rinv,r;
	__m128d rai,rai_inv,raj, raj_inv,rai_inv2,sk,sk2,lij,dlij,duij;
	__m128d uij,lij2,uij2,lij3,uij3,diff2;
	__m128d lij_inv,sk2_inv,prod,log_term,tmp,tmp_sum;
	__m128d sum_ai, tmp_ai,sk_ai,sk_aj,sk2_ai,sk2_aj,sk2_rinv;
	__m128d dadx1,dadx2;
    __m128d logterm;
	__m128d mask;
	__m128d obc_mask1,obc_mask2,obc_mask3;    
    
    __m128d oneeighth   = _mm_set1_pd(0.125);
    __m128d onefourth   = _mm_set1_pd(0.25);
    
	const __m128d half  = _mm_set1_pd(0.5);
	const __m128d three = _mm_set1_pd(3.0);
	const __m128d one   = _mm_set1_pd(1.0);
	const __m128d two   = _mm_set1_pd(2.0);
	const __m128d zero  = _mm_set1_pd(0.0);
	const __m128d neg   = _mm_set1_pd(-1.0);
	
	/* Set the dielectric offset */
	doffset   = born->gb_doffset;
	gb_radius = born->gb_radius;
    obc_param = born->param;
    work      = born->gpol_hct_work;
    jjnr      = nl->jjnr;
    dadx      = fr->dadx;
    shiftvec  = fr->shift_vec[0];
    
    jx        = _mm_setzero_pd();
    jy        = _mm_setzero_pd();
    jz        = _mm_setzero_pd();
    
    jnrA = jnrB = 0;
    
	for(i=0;i<born->nr;i++)
	{
		work[i] = 0;
	}
	
	for(i=0;i<nl->nri;i++)
	{
        ii     = nl->iinr[i];
		ii3	   = ii*3;
        is3    = 3*nl->shift[i];     
        shX    = shiftvec[is3];  
        shY    = shiftvec[is3+1];
        shZ    = shiftvec[is3+2];
        nj0    = nl->jindex[i];      
        nj1    = nl->jindex[i+1];    
        
        ix     = _mm_set1_pd(shX+x[ii3+0]);
		iy     = _mm_set1_pd(shY+x[ii3+1]);
		iz     = _mm_set1_pd(shZ+x[ii3+2]);
		        
		rai    = _mm_load1_pd(gb_radius+ii);
		rai_inv= gmx_mm_inv_pd(rai);
        
		sum_ai = _mm_setzero_pd();
		
		sk_ai  = _mm_load1_pd(born->param+ii);
		sk2_ai = _mm_mul_pd(sk_ai,sk_ai);
        
		for(k=nj0;k<nj1-1;k+=2)
		{
			jnrA        = jjnr[k];   
			jnrB        = jjnr[k+1];
			
            j3A         = 3*jnrA;  
			j3B         = 3*jnrB;
            
            GMX_MM_LOAD_1RVEC_2POINTERS_PD(x+j3A,x+j3B,jx,jy,jz);
            GMX_MM_LOAD_2VALUES_PD(gb_radius+jnrA,gb_radius+jnrB,raj);
            GMX_MM_LOAD_2VALUES_PD(obc_param+jnrA,obc_param+jnrB,sk_aj);
			
            dx    = _mm_sub_pd(ix, jx);
			dy    = _mm_sub_pd(iy, jy);
			dz    = _mm_sub_pd(iz, jz);
			
            rsq         = gmx_mm_calc_rsq_pd(dx,dy,dz);
            
            rinv        = gmx_mm_invsqrt_pd(rsq);
            r           = _mm_mul_pd(rsq,rinv);
            
			/* Compute raj_inv aj1-4 */
            raj_inv     = gmx_mm_inv_pd(raj);
            
            /* Evaluate influence of atom aj -> ai */
            t1            = _mm_add_pd(r,sk_aj);
            t2            = _mm_sub_pd(r,sk_aj);
            t3            = _mm_sub_pd(sk_aj,r);
            obc_mask1     = _mm_cmplt_pd(rai, t1);
            obc_mask2     = _mm_cmplt_pd(rai, t2);
            obc_mask3     = _mm_cmplt_pd(rai, t3);
            
            uij           = gmx_mm_inv_pd(t1);
            lij           = _mm_or_pd(   _mm_and_pd(obc_mask2,gmx_mm_inv_pd(t2)),
                                      _mm_andnot_pd(obc_mask2,rai_inv));
            dlij          = _mm_and_pd(one,obc_mask2);
            uij2          = _mm_mul_pd(uij, uij);
            uij3          = _mm_mul_pd(uij2,uij);
            lij2          = _mm_mul_pd(lij, lij);
            lij3          = _mm_mul_pd(lij2,lij);
                        
            diff2         = _mm_sub_pd(uij2,lij2);
            lij_inv       = gmx_mm_invsqrt_pd(lij2);
            sk2_aj        = _mm_mul_pd(sk_aj,sk_aj);
            sk2_rinv      = _mm_mul_pd(sk2_aj,rinv);
            prod          = _mm_mul_pd(onefourth,sk2_rinv);
                        
            logterm       = gmx_mm_log_pd(_mm_mul_pd(uij,lij_inv));
            
            t1            = _mm_sub_pd(lij,uij);
            t2            = _mm_mul_pd(diff2,
                                       _mm_sub_pd(_mm_mul_pd(onefourth,r),
                                                  prod));
            t3            = _mm_mul_pd(half,_mm_mul_pd(rinv,logterm));
            t1            = _mm_add_pd(t1,_mm_add_pd(t2,t3));
            t4            = _mm_mul_pd(two,_mm_sub_pd(rai_inv,lij));
            t4            = _mm_and_pd(t4,obc_mask3);
            t1            = _mm_mul_pd(half,_mm_add_pd(t1,t4));
                        
            sum_ai        = _mm_add_pd(sum_ai, _mm_and_pd(t1,obc_mask1) );
            
            t1            = _mm_add_pd(_mm_mul_pd(half,lij2),
                                       _mm_mul_pd(prod,lij3));
            t1            = _mm_sub_pd(t1,
                                       _mm_mul_pd(onefourth,
                                                  _mm_add_pd(_mm_mul_pd(lij,rinv),
                                                             _mm_mul_pd(lij3,r))));
            t2            = _mm_mul_pd(onefourth,
                                       _mm_add_pd(_mm_mul_pd(uij,rinv),
                                                  _mm_mul_pd(uij3,r)));
            t2            = _mm_sub_pd(t2,
                                       _mm_add_pd(_mm_mul_pd(half,uij2),
                                                  _mm_mul_pd(prod,uij3)));
            t3            = _mm_mul_pd(_mm_mul_pd(onefourth,logterm),
                                       _mm_mul_pd(rinv,rinv));
            t3            = _mm_sub_pd(t3,
                                       _mm_mul_pd(_mm_mul_pd(diff2,oneeighth),
                                                  _mm_add_pd(one,
                                                             _mm_mul_pd(sk2_rinv,rinv))));
            t1            = _mm_mul_pd(rinv,
                                       _mm_add_pd(_mm_mul_pd(dlij,t1),
                                                  _mm_add_pd(t2,t3)));
            
            dadx1         = _mm_and_pd(t1,obc_mask1);
            
            /* Evaluate influence of atom ai -> aj */
            t1            = _mm_add_pd(r,sk_ai);
            t2            = _mm_sub_pd(r,sk_ai);
            t3            = _mm_sub_pd(sk_ai,r);
            obc_mask1     = _mm_cmplt_pd(raj, t1);
            obc_mask2     = _mm_cmplt_pd(raj, t2);
            obc_mask3     = _mm_cmplt_pd(raj, t3);
            
            uij           = gmx_mm_inv_pd(t1);
            lij           = _mm_or_pd(   _mm_and_pd(obc_mask2,gmx_mm_inv_pd(t2)),
                                      _mm_andnot_pd(obc_mask2,raj_inv));
            dlij          = _mm_and_pd(one,obc_mask2);
            uij2          = _mm_mul_pd(uij, uij);
            uij3          = _mm_mul_pd(uij2,uij);
            lij2          = _mm_mul_pd(lij, lij);
            lij3          = _mm_mul_pd(lij2,lij);
                        
            diff2         = _mm_sub_pd(uij2,lij2);
            lij_inv       = gmx_mm_invsqrt_pd(lij2);
            sk2_rinv      = _mm_mul_pd(sk2_ai,rinv);
            prod          = _mm_mul_pd(onefourth,sk2_rinv);
                        
            logterm       = gmx_mm_log_pd(_mm_mul_pd(uij,lij_inv));
            
            t1            = _mm_sub_pd(lij,uij);
            t2            = _mm_mul_pd(diff2,
                                       _mm_sub_pd(_mm_mul_pd(onefourth,r),
                                                  prod));
            t3            = _mm_mul_pd(half,_mm_mul_pd(rinv,logterm));
            t1            = _mm_add_pd(t1,_mm_add_pd(t2,t3));
            t4            = _mm_mul_pd(two,_mm_sub_pd(raj_inv,lij));
            t4            = _mm_and_pd(t4,obc_mask3);
            t1            = _mm_mul_pd(half,_mm_add_pd(t1,t4));
                        
            GMX_MM_INCREMENT_2VALUES_PD(work+jnrA,work+jnrB,_mm_and_pd(t1,obc_mask1));
            
            t1            = _mm_add_pd(_mm_mul_pd(half,lij2),
                                       _mm_mul_pd(prod,lij3));
            t1            = _mm_sub_pd(t1,
                                       _mm_mul_pd(onefourth,
                                                  _mm_add_pd(_mm_mul_pd(lij,rinv),
                                                             _mm_mul_pd(lij3,r))));
            t2            = _mm_mul_pd(onefourth,
                                       _mm_add_pd(_mm_mul_pd(uij,rinv),
                                                  _mm_mul_pd(uij3,r)));
            t2            = _mm_sub_pd(t2,
                                       _mm_add_pd(_mm_mul_pd(half,uij2),
                                                  _mm_mul_pd(prod,uij3)));
            t3            = _mm_mul_pd(_mm_mul_pd(onefourth,logterm),
                                       _mm_mul_pd(rinv,rinv));
            t3            = _mm_sub_pd(t3,
                                       _mm_mul_pd(_mm_mul_pd(diff2,oneeighth),
                                                  _mm_add_pd(one,
                                                             _mm_mul_pd(sk2_rinv,rinv))));
            t1            = _mm_mul_pd(rinv,
                                       _mm_add_pd(_mm_mul_pd(dlij,t1),
                                                  _mm_add_pd(t2,t3)));
            
            dadx2         = _mm_and_pd(t1,obc_mask1);
            
            _mm_store_pd(dadx,dadx1);
            dadx += 2;
            _mm_store_pd(dadx,dadx2);
            dadx += 2;
        } /* end normal inner loop */
        
		if(k<nj1)
		{
			jnrA        = jjnr[k];   
			
            j3A         = 3*jnrA;  
            
            GMX_MM_LOAD_1RVEC_1POINTER_PD(x+j3A,jx,jy,jz);
            GMX_MM_LOAD_1VALUE_PD(gb_radius+jnrA,raj);
            GMX_MM_LOAD_1VALUE_PD(obc_param+jnrA,sk_aj);
			
            dx    = _mm_sub_sd(ix, jx);
			dy    = _mm_sub_sd(iy, jy);
			dz    = _mm_sub_sd(iz, jz);
			
            rsq         = gmx_mm_calc_rsq_pd(dx,dy,dz);
            
            rinv        = gmx_mm_invsqrt_pd(rsq);
            r           = _mm_mul_sd(rsq,rinv);
            
			/* Compute raj_inv aj1-4 */
            raj_inv     = gmx_mm_inv_pd(raj);
            
            /* Evaluate influence of atom aj -> ai */
            t1            = _mm_add_sd(r,sk_aj);
            t2            = _mm_sub_sd(r,sk_aj);
            t3            = _mm_sub_sd(sk_aj,r);
            obc_mask1     = _mm_cmplt_sd(rai, t1);
            obc_mask2     = _mm_cmplt_sd(rai, t2);
            obc_mask3     = _mm_cmplt_sd(rai, t3);
            
            uij           = gmx_mm_inv_pd(t1);
            lij           = _mm_or_pd(_mm_and_pd(obc_mask2,gmx_mm_inv_pd(t2)),
                                      _mm_andnot_pd(obc_mask2,rai_inv));
            dlij          = _mm_and_pd(one,obc_mask2);
            uij2          = _mm_mul_sd(uij, uij);
            uij3          = _mm_mul_sd(uij2,uij);
            lij2          = _mm_mul_sd(lij, lij);
            lij3          = _mm_mul_sd(lij2,lij);
            
            diff2         = _mm_sub_sd(uij2,lij2);
            lij_inv       = gmx_mm_invsqrt_pd(lij2);
            sk2_aj        = _mm_mul_sd(sk_aj,sk_aj);
            sk2_rinv      = _mm_mul_sd(sk2_aj,rinv);
            prod          = _mm_mul_sd(onefourth,sk2_rinv);
            
            logterm       = gmx_mm_log_pd(_mm_mul_sd(uij,lij_inv));
            
            t1            = _mm_sub_sd(lij,uij);
            t2            = _mm_mul_sd(diff2,
                                       _mm_sub_sd(_mm_mul_pd(onefourth,r),
                                                  prod));
            t3            = _mm_mul_sd(half,_mm_mul_sd(rinv,logterm));
            t1            = _mm_add_sd(t1,_mm_add_sd(t2,t3));
            t4            = _mm_mul_sd(two,_mm_sub_sd(rai_inv,lij));
            t4            = _mm_and_pd(t4,obc_mask3);
            t1            = _mm_mul_sd(half,_mm_add_sd(t1,t4));
            
            sum_ai        = _mm_add_sd(sum_ai, _mm_and_pd(t1,obc_mask1) );
            
            t1            = _mm_add_sd(_mm_mul_sd(half,lij2),
                                       _mm_mul_sd(prod,lij3));
            t1            = _mm_sub_sd(t1,
                                       _mm_mul_sd(onefourth,
                                                  _mm_add_sd(_mm_mul_sd(lij,rinv),
                                                             _mm_mul_sd(lij3,r))));
            t2            = _mm_mul_sd(onefourth,
                                       _mm_add_sd(_mm_mul_sd(uij,rinv),
                                                  _mm_mul_sd(uij3,r)));
            t2            = _mm_sub_sd(t2,
                                       _mm_add_sd(_mm_mul_sd(half,uij2),
                                                  _mm_mul_sd(prod,uij3)));
            t3            = _mm_mul_sd(_mm_mul_sd(onefourth,logterm),
                                       _mm_mul_sd(rinv,rinv));
            t3            = _mm_sub_sd(t3,
                                       _mm_mul_sd(_mm_mul_sd(diff2,oneeighth),
                                                  _mm_add_sd(one,
                                                             _mm_mul_sd(sk2_rinv,rinv))));
            t1            = _mm_mul_sd(rinv,
                                       _mm_add_sd(_mm_mul_sd(dlij,t1),
                                                  _mm_add_pd(t2,t3)));
            
            dadx1         = _mm_and_pd(t1,obc_mask1);
            
            /* Evaluate influence of atom ai -> aj */
            t1            = _mm_add_sd(r,sk_ai);
            t2            = _mm_sub_sd(r,sk_ai);
            t3            = _mm_sub_sd(sk_ai,r);
            obc_mask1     = _mm_cmplt_sd(raj, t1);
            obc_mask2     = _mm_cmplt_sd(raj, t2);
            obc_mask3     = _mm_cmplt_sd(raj, t3);
            
            uij           = gmx_mm_inv_pd(t1);
            lij           = _mm_or_pd(   _mm_and_pd(obc_mask2,gmx_mm_inv_pd(t2)),
                                      _mm_andnot_pd(obc_mask2,raj_inv));
            dlij          = _mm_and_pd(one,obc_mask2);
            uij2          = _mm_mul_sd(uij, uij);
            uij3          = _mm_mul_sd(uij2,uij);
            lij2          = _mm_mul_sd(lij, lij);
            lij3          = _mm_mul_sd(lij2,lij);
            
            diff2         = _mm_sub_sd(uij2,lij2);
            lij_inv       = gmx_mm_invsqrt_pd(lij2);
            sk2_rinv      = _mm_mul_sd(sk2_ai,rinv);
            prod          = _mm_mul_sd(onefourth,sk2_rinv);
            
            logterm       = gmx_mm_log_pd(_mm_mul_sd(uij,lij_inv));
            
            t1            = _mm_sub_sd(lij,uij);
            t2            = _mm_mul_sd(diff2,
                                       _mm_sub_sd(_mm_mul_sd(onefourth,r),
                                                  prod));
            t3            = _mm_mul_sd(half,_mm_mul_sd(rinv,logterm));
            t1            = _mm_add_sd(t1,_mm_add_sd(t2,t3));
            t4            = _mm_mul_sd(two,_mm_sub_sd(raj_inv,lij));
            t4            = _mm_and_pd(t4,obc_mask3);
            t1            = _mm_mul_sd(half,_mm_add_sd(t1,t4));
            
            GMX_MM_INCREMENT_1VALUE_PD(work+jnrA,_mm_and_pd(t1,obc_mask1));
            
            t1            = _mm_add_sd(_mm_mul_sd(half,lij2),
                                       _mm_mul_sd(prod,lij3));
            t1            = _mm_sub_sd(t1,
                                       _mm_mul_sd(onefourth,
                                                  _mm_add_sd(_mm_mul_sd(lij,rinv),
                                                             _mm_mul_sd(lij3,r))));
            t2            = _mm_mul_sd(onefourth,
                                       _mm_add_sd(_mm_mul_sd(uij,rinv),
                                                  _mm_mul_sd(uij3,r)));
            t2            = _mm_sub_sd(t2,
                                       _mm_add_sd(_mm_mul_sd(half,uij2),
                                                  _mm_mul_sd(prod,uij3)));
            t3            = _mm_mul_sd(_mm_mul_sd(onefourth,logterm),
                                       _mm_mul_sd(rinv,rinv));
            t3            = _mm_sub_sd(t3,
                                       _mm_mul_sd(_mm_mul_sd(diff2,oneeighth),
                                                  _mm_add_sd(one,
                                                             _mm_mul_sd(sk2_rinv,rinv))));
            t1            = _mm_mul_sd(rinv,
                                       _mm_add_sd(_mm_mul_sd(dlij,t1),
                                                  _mm_add_sd(t2,t3)));
            
            dadx2         = _mm_and_pd(t1,obc_mask1);
            
            _mm_store_pd(dadx,dadx1);
            dadx += 2;
            _mm_store_pd(dadx,dadx2);
            dadx += 2;
        } 
        gmx_mm_update_1pot_pd(sum_ai,work+ii);
        
	}
	
	/* Parallel summations */
	if(PARTDECOMP(cr))
	{
		gmx_sum(natoms, work, cr);
	}
	else if(DOMAINDECOMP(cr))
	{
		dd_atom_sum_real(cr->dd, work);
	}
	
    if(gb_algorithm==egbHCT)
    {
        /* HCT */
        for(i=0;i<fr->natoms_force;i++) /* PELA born->nr */
        {
			if(born->use[i] != 0)
            {
                rr      = top->atomtypes.gb_radius[md->typeA[i]]-doffset; 
                sum     = 1.0/rr - work[i];
                min_rad = rr + doffset;
                rad     = 1.0/sum; 
                
                born->bRad[i]   = rad > min_rad ? rad : min_rad;
                fr->invsqrta[i] = gmx_invsqrt(born->bRad[i]);
            }
        }
        
        /* Extra communication required for DD */
        if(DOMAINDECOMP(cr))
        {
            dd_atom_spread_real(cr->dd, born->bRad);
            dd_atom_spread_real(cr->dd, fr->invsqrta);
        }
    }
    else
    {
        /* OBC */
        for(i=0;i<fr->natoms_force;i++) /* PELA born->nr */
        {
			if(born->use[i] != 0)
            {
                rr      = top->atomtypes.gb_radius[md->typeA[i]];
                rr_inv2 = 1.0/rr;
                rr      = rr-doffset; 
                rr_inv  = 1.0/rr;
                sum     = rr * work[i];
                sum2    = sum  * sum;
                sum3    = sum2 * sum;
                
                tsum    = tanh(born->obc_alpha*sum-born->obc_beta*sum2+born->obc_gamma*sum3);
                born->bRad[i] = rr_inv - tsum*rr_inv2;
                born->bRad[i] = 1.0 / born->bRad[i];
                
                fr->invsqrta[i]=gmx_invsqrt(born->bRad[i]);
                
                tchain  = rr * (born->obc_alpha-2*born->obc_beta*sum+3*born->obc_gamma*sum2);
                born->drobc[i] = (1.0-tsum*tsum)*tchain*rr_inv2;
            }
        }
        /* Extra (local) communication required for DD */
        if(DOMAINDECOMP(cr))
        {
            dd_atom_spread_real(cr->dd, born->bRad);
            dd_atom_spread_real(cr->dd, fr->invsqrta);
            dd_atom_spread_real(cr->dd, born->drobc);
        }
    }
    
	
	
	return 0;
}