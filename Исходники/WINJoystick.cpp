void CJoystick::Initialize()
{
  if (!IsEnabled())
    return;

  HRESULT hr;

  // clear old joystick names
  ReleaseJoysticks();
  CSingleLock lock(m_critSection);

  if( FAILED( hr = DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION, IID_IDirectInput8, ( VOID** )&m_pDI, NULL ) ) )
  {
    CLog::Log(LOGDEBUG, __FUNCTION__" : Failed to create DirectInput");
    return;
  }

  if( FAILED( hr = m_pDI->EnumDevices( DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, this, DIEDFL_ATTACHEDONLY ) ) )
    return;

  if(m_pJoysticks.size() == 0)
  {
    CLog::Log(LOGDEBUG, __FUNCTION__" : No Joystick found");
    return;
  }

  for(std::vector<LPDIRECTINPUTDEVICE8>::iterator it = m_pJoysticks.begin(); it != m_pJoysticks.end(); ++it)
  {
    LPDIRECTINPUTDEVICE8 pJoy = (*it);
    // Enumerate the joystick objects. The callback function enabled user
    // interface elements for objects that are found, and sets the min/max
    // values property for discovered axes.
    if( FAILED( hr = pJoy->EnumObjects( EnumObjectsCallback, pJoy, DIDFT_ALL ) ) )
      CLog::Log(LOGDEBUG, __FUNCTION__" : Failed to enumerate objects");
  }

  m_JoyId = -1;

  // Set deadzone range
  SetDeadzone(g_advancedSettings.m_controllerDeadzone);
}