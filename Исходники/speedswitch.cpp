//------------------------------------------------------------------
// check power scheme integrity
//
// check: 0=no consistency check
//        1=check power scheme only
//        2=check processor scheme only
//        3=check both power and processor scheme
//------------------------------------------------------------------
BOOL checkProfile( int check )
{
  log( _T("Checking power scheme integrity ...") );
  
  CString err;
  err.LoadStringW( IDS_MAINERR2 );

  POWER_POLICY policyTemp;
  MACHINE_PROCESSOR_POWER_POLICY machTemp;
  static TCHAR msg[1024];   // für diverse Fehlertexte
  BOOL forceActivate = FALSE;

  if( !ReadPwrScheme(internalProfile,&policyTemp) )
  {
    log( _T("Recreating power scheme ...") );
    UINT x = internalProfile;

    if( !WritePwrScheme(&x,L"Speedswitch Control",L"\0\0",&internalPolicy) )
    {
      CString s1;
      s1.LoadStringW( IDS_SW1 );
      wsprintf( msg, s1, GetLastError() );
      MessageBox( NULL, msg, err, MB_ICONEXCLAMATION|MB_OK );
      return FALSE;
    }

    forceActivate = TRUE;
  }
  else if( check&1 )
  {
    if( !comparePowerProfile(policyTemp,internalPolicy) )
    {
      log( _T("Restoring power scheme data ...") );
      UINT x = internalProfile;

      if( !WritePwrScheme(&x,L"Speedswitch Control",L"\0\0",&internalPolicy) )
      {
        CString s1;
        s1.LoadStringW( IDS_SW2 );
        wsprintf( msg, s1, GetLastError() );
        MessageBox( NULL, msg, err, MB_ICONEXCLAMATION|MB_OK );
        return FALSE;
      }

      forceActivate = TRUE;
    }
  }

  if( !ReadProcessorPwrScheme(internalProfile,&machTemp) )
  {
    log( _T("Recreating processor scheme ...") );
    if( !WriteProcessorPwrScheme(internalProfile,&mach) )
    {
      CString s1;
      s1.LoadStringW( IDS_SW3 );
      wsprintf( msg, s1, GetLastError() );
      MessageBox( NULL, msg, err, MB_ICONEXCLAMATION|MB_OK );
      return FALSE;
    }   

    forceActivate = TRUE;
  }
  else if( check&2 )
  {
    if( !compareCPUScheme(machTemp,mach) )
    {
      log( _T("Restoring processor scheme data ...") );
      if( !WriteProcessorPwrScheme(internalProfile,&mach) )
      {
        CString s1;
        s1.LoadStringW( IDS_SW4 );
        wsprintf( msg, s1, GetLastError() );
        MessageBox( NULL, msg, err, MB_ICONEXCLAMATION|MB_OK );
        return FALSE;
      }  

      forceActivate = TRUE;
    }
  }

  UINT profile;

  if( !GetActivePwrScheme(&profile) )
  {
    CString s1;
    s1.LoadStringW( IDS_SW5 );
    wsprintf( msg, s1, GetLastError() );
    MessageBox( NULL, msg, err, MB_OK|MB_ICONEXCLAMATION );
    return FALSE;
  }

  if( forceActivate || profile!=internalProfile )
  {
    log( _T("Reactivating power scheme (%d, %d) ..."), profile, internalProfile );
    if( !SetActivePwrScheme(internalProfile,NULL,NULL) )
    {
      CString s1;
      s1.LoadStringW( IDS_SW6 );
      wsprintf( msg, s1, GetLastError() );
      MessageBox( NULL, msg, err, MB_ICONEXCLAMATION|MB_OK );
      return FALSE;
    }
  }

  return TRUE;
}