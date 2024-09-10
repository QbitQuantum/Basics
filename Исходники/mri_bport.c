MRI_IMAGE * mri_bport_contig( float dt , float fbot , float ftop ,
                              int ntime , int nbefore , int nafter )
{
   MRI_IMAGE *fim ; float *far , *fii , *fip ;
   int nfbot , nftop , ff , ii,jj , nev=(ntime%2==0) , ncol,nrow ;
   float df , freq ;

ENTRY("mri_bport_contig") ;

   if( dt   <= 0.0f ) dt   = 1.0f ;
   if( fbot <  0.0f ) fbot = 0.0f ;
   if( ntime < 9 || ftop < fbot ) RETURN(NULL) ;
   if( nbefore < 0 ) nbefore = 0 ;
   if( nafter  < 0 ) nafter  = 0 ;

   df  = 1.0f / (ntime * dt) ;  /* frequency spacing */

   nfbot = (int)rintf(fbot/df+0.1666666f) ;
   if( nfbot > ntime/2    ) nfbot = ntime/2 ;
   if( nfbot < BP_ffbot   ) nfbot = BP_ffbot ;

   nftop = (int)rintf(ftop/df-0.1666666f) ;
   if( nftop < nfbot   ) nftop = nfbot   ;
   if( nftop > ntime/2 ) nftop = ntime/2 ;
#if 1
   ININFO_message("Frequency indexes: blocklen=%d nfbot=%d nftop=%d",ntime,nfbot,nftop) ;
#endif

   ncol = 2*(nftop-nfbot-1) ; if( ncol < 0 ) ncol = 0 ;
   ncol += (nfbot == 0 || (nfbot == ntime/2 && nev==1) ) ? 1 : 2 ;
   if( nftop > nfbot )
     ncol += (nftop == ntime/2 && nev) ? 1 : 2 ;

   if( ncol <= 0 ){
     ININFO_message("Failure :-(") ; RETURN(NULL) ;  /* should never happen */
   }

   nrow = ntime + nbefore + nafter ;
   fim  = mri_new( nrow , ncol , MRI_float ) ;
   far  = MRI_FLOAT_PTR(fim) ;

   for( ii=0,ff=nfbot ; ff <= nftop ; ff++ ){
     fii = far + (ii*nrow + nbefore) ;
     if( ff == 0 ){
       for( jj=0 ; jj < ntime ; jj++ ) fii[jj] = 1.0f ;
       ii++ ;
     } else if( ff == ntime/2 && nev ){
       for( jj=0 ; jj < ntime ; jj++ ) fii[jj] = 2*(jj%2)-1 ;
       ii++ ;
     } else {
       fip = fii + nrow ; freq = ff*df * (2.0f*3.141593f) * dt ;
       for( jj=0 ; jj < ntime ; jj++ ){
         fii[jj] = cos(freq*jj) ; fip[jj] = sin(freq*jj) ;
       }
       ii += 2 ;
     }
   }

   RETURN(fim) ;
}