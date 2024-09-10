void mri_metrics_pp( MRI_IMAGE *imp , MRI_IMAGE *imq , float *met , byte *mmm )
{
   int nvox , nmmm=0 ;
   int *rst , *pst , *qst ;
   byte *par, *qar ;
   float qj,rij , rat,tmp,lrr,rm1,rp1 , fac ;
   float esum,tsum,hsum , jsum,dsum,xsum , qsum,asum ;
   register int ii,jj,kk ;
   MRI_IMAGE *imqq, *impp ;

   if( imp == NULL || imq == NULL            ) return ;
   if( met == NULL || imp->nvox != imq->nvox ) return ;

   nvox = imp->nvox ;

   impp = (imp->kind==MRI_byte) ? imp : mri_to_byte(imp) ;
   imqq = (imq->kind==MRI_byte) ? imq : mri_to_byte(imq) ;
   par  = MRI_BYTE_PTR(impp) ;
   qar  = MRI_BYTE_PTR(imqq) ;

   pst = (int *)calloc(256    ,sizeof(int)) ;
   qst = (int *)calloc(256    ,sizeof(int)) ;
   rst = (int *)calloc(256*256,sizeof(int)) ;

   if( mmm != NULL ){
     for( kk=0 ; kk < nvox ; kk++ ) if( mmm[kk] ) nmmm++ ;
     fac = 1.0f / nmmm ;
     for( kk=0 ; kk < nvox ; kk++ ){
       if( mmm[kk] == 0 ) continue ;
       ii = par[kk] ; jj = qar[kk] ;
       pst[ii]++ ; qst[jj]++ ; rst[ii+256*jj]++ ;
     }
   } else {
     fac = 1.0f / nvox ;
     for( kk=0 ; kk < nvox ; kk++ ){
       ii = par[kk] ; jj = qar[kk] ;
       pst[ii]++ ; qst[jj]++ ; rst[ii+256*jj]++ ;
     }
   }

   esum = tsum = hsum = 0.0f ;
   jsum = dsum = xsum = 0.0f ;
   qsum = asum =        0.0f ;
   for( jj=0 ; jj < 256 ; jj++ ){
     qj = (float)qst[jj] ;
     if( qj > 0.0f ){
       kk = 256*jj ; qj *= fac ;
       for( ii=0 ; ii < 256 ; ii++ ){
         rij = (float)rst[ii+kk] ;
         if( rij > 0.0f ){
           rat = (qj *(float)pst[ii]) / rij ;
           lrr = logf(rat) ;

           esum += rij * lrr ;
           tmp   = 1.0f/sqrtf(rat)-1.0f ; hsum += rij * tmp ;
           tmp   = 1.0f/cbrtf(rat)-1.0f ; qsum += rij * tmp ;
           tmp   = lrr*lrr*lrr          ; asum += rij * tmp ;
         }
       }
     }
   }

   free((void*)rst); free((void*)qst); free((void*)pst);
   if( impp != imp ) mri_free(impp);
   if( imqq != imq ) mri_free(imqq);

   met[0] = -fac * esum * 0.5f ;
   met[1] =  fac * hsum * 0.5f ;
   met[2] =  fac * qsum ;
   return ;
}