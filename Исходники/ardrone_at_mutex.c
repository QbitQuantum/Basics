AT_CODEC_ERROR_CODE host_shutdown( void )
{
  if( func_ptrs.shutdown != NULL )
     func_ptrs.shutdown();

  ardrone_at_shutdown();

  return AT_CODEC_SHUTDOWN_OK;
}