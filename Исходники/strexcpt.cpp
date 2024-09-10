void InstallOldStructuredExceptionHandler( void )
{
  if ( !IsDebuggerPresent() )
  {
    _set_se_translator( alt_se_trans_func );
  }
}