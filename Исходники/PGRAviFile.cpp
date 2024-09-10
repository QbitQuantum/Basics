int
PGRAviFile::enumerateCompressors( int  iRows, int iCols, int iBPP, 
                                  ICINFO* picinfo, int iNumICInfo )
{
   // If picinfo is NULL, then we are retreiving the number of
   // usable compressors at the current settings so we can allocate
   // enough memory.
   bool bpicinfoNull = picinfo == NULL;

   ICINFO* picinfoTemp = new ICINFO[ 50 ];

   HIC hic;
   
   BITMAPINFOHEADER bih; 
   
   // Initialize the bitmap structure. 
   bih.biSize          = sizeof( BITMAPINFOHEADER );
   bih.biPlanes        = 1;
   bih.biCompression   = BI_RGB;
   bih.biXPelsPerMeter = 100;
   bih.biYPelsPerMeter = 100;
   bih.biClrUsed       = 0;
   bih.biClrImportant  = 0;
   bih.biWidth         = iCols;
   bih.biHeight        = iRows;
   bih.biBitCount      = (unsigned short)iBPP;
   
   bih.biSizeImage = 
      bih.biWidth * bih.biHeight * ( bih.biBitCount / 8 );

   int  iNumCompressors = 0;
   bool bICInfoFull     = false;
   
   for( int i = 0; ICInfo( 0, i, &picinfoTemp[ i ] ) && !bICInfoFull; i++ ) 
   { 
      // Open the compressor so we can query it.
      hic = ICOpen( picinfoTemp[ i ].fccType, 
         picinfoTemp[ i ].fccHandler, ICMODE_QUERY ); 
      
      if( hic ) 
      { 
         // Skip this compressor if it can't handle the format. 
         if( ICCompressQuery( hic, &bih, 0 ) != ICERR_OK ) 
         { 
            ICClose( hic ); 
            continue; 
         } 
         
         // Find out the compressor info. 
         if( !bpicinfoNull )
         {
            ICGetInfo( hic, &picinfo[ iNumCompressors ], sizeof( ICINFO ) );
         }

         iNumCompressors++;

         if( !bpicinfoNull && (iNumCompressors == iNumICInfo) )
         {
            bICInfoFull = true;
         }
         
         // Close the compressor.
         ICClose( hic ); 
      } 
   } 

   delete [] picinfoTemp;

   return iNumCompressors;
}