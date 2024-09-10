void VideoFrameDesc::setParameters( const ProfileLoader::Profile& profile )
{
	// width
	if( profile.count( constants::avProfileWidth ) )
		setWidth( atoi( profile.find( constants::avProfileWidth )->second.c_str() ) );
	// height
	if( profile.count( constants::avProfileHeight ) )
		setHeight( atoi( profile.find( constants::avProfileHeight )->second.c_str() ) );
	// pixel format	
	if( profile.count( constants::avProfilePixelFormat ) )
		setPixelFormat( profile.find( constants::avProfilePixelFormat )->second );
	// fps
	if( profile.count( constants::avProfileFrameRate ) )
		setFps( atof( profile.find( constants::avProfileFrameRate )->second.c_str() ) );
}