int cScrnRest( int iLeft, int iTop, char *cScrFile,
               int image_ops, int iDelFlag, int iMoveFlag )
{
   struct xScrFileHEADER  xScr;              // Screen file header
   FHANDLE fhandle;                          // Screen file handle
   unsigned char *imgbuf;                    // image buffer
   unsigned int isize;                       // image size variable
   unsigned int iRowCnt;                     // row counter
   int iCnt;                                 // image counter


   if(iMoveFlag != MPIXEL)
     {
       iLeft   = iscale(iLeft  , SCALE_X , SCR_SCALE);
       iTop    = iscale(iTop   , SCALE_Y , SCR_SCALE);
      }


   // Open screen input file
   fhandle = _fsOpen(cScrFile, FO_READ|FO_SHARED);

   if (_fsError())
      return( grSCR_IOERROR );

   // Read Screen File Header
   _fsRead(fhandle,(BYTEP)&xScr, sizeof(xScr));

   // Check Screen file for signature word
   if ( xScr.scrType != SCR_SIGNATURE_WORD)
      {
         _fsClose(fhandle);
         return( grSCR_UNSUPPORTED );
      }

   // Position file pointer to start of screen image
   _fsSeek(fhandle, xScr.lOffBits , FS_SET);

   isize = max( xScr.iSizeImage, xScr.iLastImage);

   // allocate largest memory required to hold the image
   imgbuf = _xalloc(isize);

   if (imgbuf == NULL)
      {
         _fsClose(fhandle);
         return( grSCR_NOMEMORY );
      }


   iRowCnt = iTop;

   for ( iCnt = 1; iCnt <= xScr.iImgCount; iCnt++ )
    {

      if( iCnt == xScr.iImgCount )
          isize = xScr.iLastImage;
      else
          isize = xScr.iSizeImage;

      // Read Image buffer
      _fsRead(fhandle, imgbuf, isize);

      // display the image
      putimage(iLeft, iRowCnt, imgbuf, image_ops);

      iRowCnt += xScr.iRowIncr + 1;

    }

   // clean-up code
   _xfree(imgbuf);
   _fsClose(fhandle);

   // delete screen file
   if (iDelFlag)
      _fsDelete (cScrFile);

   return( grSCR_OKAY );
}