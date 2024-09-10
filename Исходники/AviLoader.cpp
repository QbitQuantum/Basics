void CAviLoader::close()
{
    if( getframe )
        AVIStreamGetFrameClose( getframe );

    if( avistream )
        AVIStreamRelease( avistream );

    if( avifile )
        AVIFileRelease( avifile );

    if(frame)
	{
		delete []frame;
		frame = NULL;
	}

    init();
}