MRI_IMAGE * mri_principal_vector( MRI_IMARR *imar )
{
   int nx , nvec , ii,jj,kk , nev ;
   float *amat , *umat , *sval ;
   float *far , *tar ; MRI_IMAGE *tim ;
   float vmean=0.0f , vnorm=0.0f ;
   register float sum , zum ; float qum ;

   if( imar == NULL ) return NULL ;
   nvec = IMARR_COUNT(imar) ;       if( nvec < 1 ) return NULL ;
   nx   = IMARR_SUBIM(imar,0)->nx ; if( nx   < 1 ) return NULL ;

#define A(i,j) amat[(i)+(j)*nx]     /* nx X nvec matrix */
#define U(i,j) umat[(i)+(j)*nx]     /* ditto */
#define X(i,j) amat[(i)+(j)*nvec]   /* nvec X nx matrix */

   nev  = mpv_sitop + 1 ;

   amat = (float *)malloc( sizeof(float)*nx*nvec ) ;
   umat = (float *)malloc( sizeof(float)*nx*nev  ) ;
   sval = (float *)malloc( sizeof(float)*nev     ) ;

   /* load data vectors into A */

   for( jj=0 ; jj < nvec ; jj++ ){
     tim = IMARR_SUBIM(imar,jj) ;
     far = MRI_FLOAT_PTR(tim) ;
     for( ii=0 ; ii < nx ; ii++ ) A(ii,jj) = far[ii] ;
   }

   /* remove mean of each vector? */

   if( mpv_vmean ){
     for( jj=0 ; jj < nvec ; jj++ ){
       sum = 0.0 ;
       for( ii=0 ; ii < nx ; ii++ ) sum += A(ii,jj) ;
       sum /= nx ; if( jj == 0 ) vmean = sum ;
       for( ii=0 ; ii < nx ; ii++ ) A(ii,jj) -= sum ;
     }
   }

   /* normalize each vector? */

   if( mpv_vnorm ){
     for( jj=0 ; jj < nvec ; jj++ ){
       sum = 0.0f ;
       for( ii=0 ; ii < nx ; ii++ ) sum += A(ii,jj)*A(ii,jj) ;
       if( sum > 0.0f ){
         sum = 1.0f / sqrtf(sum) ; if( jj == 0 ) vnorm = 1.0f/sum ;
         for( ii=0 ; ii < nx ; ii++ ) A(ii,jj) *= sum ;
       }
     }
   }

   /* do the eigen-stuff */

   jj = first_principal_vectors( nx,nvec,amat , nev,sval,umat ) ;
   if( jj <= 0 ){ free(sval); free(umat); free(amat); return NULL; }
   nev = jj ;

   if( mpv_evnum > 0 ){
     int itop = MIN(mpv_evnum,nev) ;
     for( ii=0 ; ii < itop      ; ii++ ) mpv_ev[ii] = sval[ii] ;
     for(      ; ii < mpv_evnum ; ii++ ) mpv_ev[ii] = 0.0f ;
   }

   tim = mri_new( nx , nev , MRI_float ) ;
   far = MRI_FLOAT_PTR(tim) ;
   for( jj=0 ; jj < nev ; jj++ ){
     tar = far + jj*nx ;
     for( ii=0 ; ii < nx ; ii++ ) tar[ii] = U(ii,jj) ;
   }

   /* select sign of result vector(s), then scale */

   for( kk=0 ; kk < nev ; kk++ ){  /* loop over multiple output vectors */
     tar = far + kk*nx ;
     qum = 0.0f ;
     if( mpv_sign_meth == 0 ){         /* mean of dot products with data vectors */
       for( jj=0 ; jj < nvec ; jj++ ){
         zum = sum = 0.0f ;
         for( ii=0 ; ii < nx ; ii++ ){ sum += A(ii,jj)*tar[ii]; zum += A(ii,jj)*A(ii,jj); }
         if( zum > 0.0f ){
           sum = sum / zum ; sum = MIN(sum,0.9999f) ; sum = MAX(sum,-0.9999f) ;
           qum += atanhf(sum) ;
         }
       }
     } else {                          /* dot product with mean data vector */
       for( ii=0 ; ii < nx ; ii++ ){
         sum = 0.0f ;
         for( jj=0 ; jj < nvec ; jj++ ) sum += A(ii,jj) ;  /* mean vec at time ii */
         qum += sum * tar[ii] ;
       }
     }
     if( qum < 0.0f ){
       for( ii=0 ; ii < nx ; ii++ ) tar[ii] = -tar[ii] ;
     }
     sum = 0.0f ;
     for( ii=0 ; ii < nx ; ii++ ) sum += tar[ii]*tar[ii] ;
     if( sum > 0.0f && fabs(sum-1.0f) > 1.e-5f ){
       sum = 1.0f / sum ; for( ii=0 ; ii < nx ; ii++ ) tar[ii] *= sum ;
     }
   }

   free(sval); free(umat); free(amat); return tim;
}