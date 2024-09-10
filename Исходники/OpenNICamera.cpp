    void OpenNICamera::stopIRCapture()
    {
        if( !_irGen.IsGenerating() )
            return;

        XnStatus status = XN_STATUS_OK;
        status = _irGen.StopGenerating();
        if( status != XN_STATUS_OK ){
            String msg;
            msg.sprintf( "Could not stop generating IR Image: %s", xnGetStatusString( status ) );
            throw CVTException( msg.c_str() );
        }
    }