/*清除摄像头系统信息, 这里把内存的对应的所有数据都保存到了文件中*/ 
void camera_pro_system_close( void )
{
	/*写入配置文件*/
#if 0
	camera_profile_format cmr_file;
	int write_byte = 0;
	
	write_byte = sizeof(preset_point_format)*PRESET_NUM_MAX;
	memcpy( cmr_file.cmr_preset_list, gpresetcmr_list, write_byte );
	camera_profile_fill_check( &cmr_file, PRESET_NUM_MAX );
	// 从头写入
	if( -1 != Fseek( gpreset_fd, 0, SEEK_SET))
	{
		camera_profile_write( gpreset_fd, &cmr_file );
		Fflush( gpreset_fd );
	}
#endif
	/*2016-1-26不能正常关闭*/ 
	if( gpreset_fd != NULL )
	{
		DEBUG_INFO( "============>camera system close Success!<=======" );
		camera_profile_close( gpreset_fd );
		gpreset_fd = NULL;
	}

	DEBUG_INFO( "============>camera system close Success!<=======" );
}