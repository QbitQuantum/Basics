__NO_RETURN void play_dead( void )
{
  osKernelLock( );
  while( 1 )
  {
    __NOP( );
  }
}  