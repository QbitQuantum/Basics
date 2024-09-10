void TPZRunnableComponent :: postRun(uTIME time)
{
   if( m_Flow )
   {
      m_Flow -> postRun(time);
   }
   else
   {
      TPZString err;
      err.sprintf(ERR_TPZRUNCO_001, (char*)asString() );
      EXIT_PROGRAM(err);
   }
}