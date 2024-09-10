// For writeScanLines... we don't want to call the ExifJpegImage's
// writeScanLines at this time, since it will immediately write 
// the compressed stream directly to the file. We need to delay
// this write until the close of the image file so that the writing
// of the compressed stream is coordinated with the writing of the
// application segments. Two ways to do this. First, do the compression
// now, but have the ExifJpegImage write it to a temporary buffer, then
// we write this compressed data stream to the image file during the close.
// Second, we hold onto the reference to the ExifImageDesc passed in and
// do the compression and writing to the file during the close. Right now,
// I think the first is the best way to go...
ExifStatus 
ExifImageFile::writeScanLines( ExifImageDesc &imgDesc, exif_uint32 numLines, 
                               exif_uint32 &nextLine, exif_uint32& linesCompressed )
{ 

    // write to a temp file
    ExifStatus status = EXIF_ERROR;
    if( mTmpImageFile.size() == 0 )
    {
#ifdef _MSC_VER
 	    // Windows' _tempnam automatically uses the
	    // TMP environmental variable if it's present,
	    // otherwise it will use the "C:\\temp" directory.
	    mTmpImageFile = _tempnam("C:\\temp","oet");
        status = mOutImage.open( mTmpImageFile.c_str(), "w" ) ;
#elif (defined(__GNUC__) && (__GNUC__ > 2))
        // GCC Linkers always complain about the unsafe nature of
        // of tmpnam().  So here's a work-around. using mkstemp.
        // It's not great, but it works "safely".
        char tmpFileName[L_tmpnam];
        int len = strlen(P_tmpdir);
        strncpy(tmpFileName,P_tmpdir,len);
        strncpy(&tmpFileName[len],"/OpenExifXXXXXX",16);
        int tfd = mkstemp(tmpFileName);
        FILE * tf = fdopen(tfd,"w+");
        status = mOutImage.open(tf,tmpFileName,"w");
        mTmpImageFile = tmpFileName;
#else
        mTmpImageFile = tmpnam(NULL) ;
        status = mOutImage.open( mTmpImageFile.c_str(), "w" ) ;
#endif
    }

    if( status == EXIF_OK )
    {
        mImageModifiedOrCreated = true ;

        if( mICCProf != NULL )
        {
            mOutImage.setICCProfile(mICCProf,mICCProfSize);
            mICCProf = NULL;
        }


        status = mOutImage.writeScanLines( imgDesc, numLines,
            nextLine, linesCompressed ) ;
        mOutImage.close() ;
    }
    return status ;
}