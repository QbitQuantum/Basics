INT WINAPI DOSVM_Enter( CONTEXT86 *context )
{
  INT ret = 0;
  if (!ISV86(context))
      ERR( "Called with protected mode context!\n" );

  __TRY
  {
      if (!WOWCallback16Ex( 0, WCB16_REGS, 0, NULL, (DWORD *)context )) ret = -1;
      TRACE_(module)( "ret %d err %u\n", ret, GetLastError() );
  }
  __EXCEPT(exception_handler)
  {
    TRACE_(module)( "leaving vm86 mode\n" );
  }
  __ENDTRY

  return ret;
}