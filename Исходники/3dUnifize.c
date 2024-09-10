void mri_invertcontrast_inplace( MRI_IMAGE *im , float uperc , byte *mask )
{
   byte *mmm=NULL ;
   int nvox , nhist , ii ; float *hist=NULL , *imar , ucut ;

   if( im == NULL || im->kind != MRI_float ) return ;
        if( uperc <  90.0f ) uperc =  90.0f ;
   else if( uperc > 100.0f ) uperc = 100.0f ;

   mmm = mask ;
   if( mmm == NULL ) mmm = mri_automask_image(im) ;

   nvox = im->nvox ;
   hist = (float *)malloc(sizeof(float)*nvox) ;
   imar = MRI_FLOAT_PTR(im) ;
   for( nhist=ii=0 ; ii < nvox ; ii++ ){ if( mmm[ii] ) hist[nhist++] = imar[ii]; }
   if( nhist < 100 ){
     if( mmm != mask ) free(mmm) ;
     free(hist) ; return ;
   }
   qsort_float(nhist,hist) ;
   ii = (int)rintf(nhist*uperc*0.01f) ; ucut = hist[ii] ; free(hist) ;
   for( ii=0 ; ii < nvox ; ii++ ){
     if(  mmm[ii]                    ) imar[ii] = ucut - imar[ii] ;
     if( !mmm[ii] || imar[ii] < 0.0f ) imar[ii] = 0.0f ;
   }
   if( mmm != mask ) free(mmm) ;
   return ;
}