int camera_profile_read( FILE *fd, camera_profile_format *read_buf )
{
	assert( fd && read_buf );
	int ret = Fread( fd, read_buf, sizeof(camera_profile_format), 1 );
	if( ret != 1 )
	{
		DEBUG_ERR( "camera_profile_read ERROR!" );
		ret = -1;
	}

	return ret;
}