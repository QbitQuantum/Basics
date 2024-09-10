void CvCaptureAVI_VFW::close()
{
    if( getframe )
        AVIStreamGetFrameClose( getframe );

    if( avistream )
        AVIStreamRelease( avistream );

    if( avifile )
        AVIFileRelease( avifile );

    cvReleaseImage( &frame );
    init();
}