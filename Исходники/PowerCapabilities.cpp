void CPowerCapabilities::setVars()
{
  yes.LoadStringW( IDS_PINF19 );
  no.LoadStringW( IDS_PINF20 );

  BOOL x = (CallNtPowerInformation(SystemPowerCapabilities,
                                   NULL,
                                   0,
                                   &spc,
                                   sizeof(spc)) == ERROR_SUCCESS);
  if( x )
  {
    m_szPowerButton = (spc.PowerButtonPresent ? yes : no );
    m_szSleepButton = (spc.SleepButtonPresent ? yes : no );
    m_szLidSwitch = (spc.LidPresent ? yes : no );

    wchar_t text[128] = _T("");
    bool first = true;

    if( spc.SystemS1 ) 
    {
      _tcscat_s( text, _T("S1") );
      first = false;
    }

    if( spc.SystemS2 )
    {
      if( !first )
        _tcscat_s( text, _T(", ") );
      _tcscat_s( text, _T("S2") );
      first = false;
    }

    if( spc.SystemS3 )
    {
      if( !first )
        _tcscat_s( text, _T(", ") );
      _tcscat_s( text, _T("S3") );
      first = false;
    }

    if( spc.SystemS4 )
    {
      if( !first )
        _tcscat_s( text, _T(", ") );
      _tcscat_s( text, _T("S4") );
      first = false;
    }

    if( spc.SystemS5 )
    {
      if( !first )
        _tcscat_s( text, _T(", ") );
      _tcscat_s( text, _T("S5") );
      first = false;
    }
    
    m_szSStates = text;
    m_szHiberFile = (spc.HiberFilePresent ? yes : no );
    m_szWakeSupport = (spc.FullWake ? yes : no );
    m_szVideoDim = (spc.VideoDimPresent ? yes : no );
    m_szAPMBios = (spc.ApmPresent ? yes : no );
    m_szUPSPresent = (spc.UpsPresent ? yes : no );
    m_szThermalZones = (spc.ThermalControl ? yes : no );

    BOOLEAN throttle = spc.ProcessorThrottle;

    m_szThrottle = (throttle ? yes : no);

    if( throttle )
    {
      m_szThrottleMax.Format( _T("%d"), spc.ProcessorMinThrottle );
      m_szThrottleMin.Format( _T("%d"), spc.ProcessorMaxThrottle );
    }
    else
    {
      m_szThrottleMax = _T("---");
      m_szThrottleMin = _T("---");
    }

    m_szSpinDown = (spc.DiskSpinDown ? yes : no );
    m_szSystemBatteries = (spc.SystemBatteriesPresent ? yes : no );
    m_szShortTermBatteries = (spc.BatteriesAreShortTerm ? yes : no );
  }
}