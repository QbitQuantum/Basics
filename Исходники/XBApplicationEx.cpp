//-----------------------------------------------------------------------------
// Name: Run()
// Desc:
//-----------------------------------------------------------------------------
INT CXBApplicationEx::Run()
{
  CLog::Log(LOGNOTICE, "Running the application..." );

  // Get the frequency of the timer
  LARGE_INTEGER qwTicksPerSec;
  QueryPerformanceFrequency( &qwTicksPerSec );
  FLOAT fSecsPerTick = 1.0f / (FLOAT)qwTicksPerSec.QuadPart;

  // Save the start time
  LARGE_INTEGER qwTime, qwLastTime, qwElapsedTime;
  QueryPerformanceCounter( &qwTime );
  qwLastTime.QuadPart = qwTime.QuadPart;

  LARGE_INTEGER qwAppTime, qwElapsedAppTime;
  qwAppTime.QuadPart = 0;
  qwElapsedTime.QuadPart = 0;
  qwElapsedAppTime.QuadPart = 0;

  BYTE processExceptionCount = 0;
  BYTE frameMoveExceptionCount = 0;
  BYTE renderExceptionCount = 0;

#ifndef _DEBUG
  const BYTE MAX_EXCEPTION_COUNT = 10;
#endif

  // Run the game loop, animating and rendering frames
  while (!m_bStop)
  {
#ifdef HAS_PERFORMANCE_SAMPLE
    CPerformanceSample sampleLoop("XBApplicationEx-loop");  
#endif

    //-----------------------------------------
    // Perform app timing
    //-----------------------------------------

    // Check Start button
#ifdef HAS_GAMEPAD
    if ( m_DefaultGamepad.wPressedButtons & XINPUT_GAMEPAD_START )
#endif
      m_bPaused = !m_bPaused;

    // Get the current time (keep in LARGE_INTEGER format for precision)
    QueryPerformanceCounter( &qwTime );
    qwElapsedTime.QuadPart = qwTime.QuadPart - qwLastTime.QuadPart;
    qwLastTime.QuadPart = qwTime.QuadPart;
    if ( m_bPaused )
      qwElapsedAppTime.QuadPart = 0;
    else
      qwElapsedAppTime.QuadPart = qwElapsedTime.QuadPart;
    qwAppTime.QuadPart += qwElapsedAppTime.QuadPart;

    // Store the current time values as floating point
    m_fTime = fSecsPerTick * ((FLOAT)(qwTime.QuadPart));
    m_fElapsedTime = fSecsPerTick * ((FLOAT)(qwElapsedTime.QuadPart));
    m_fAppTime = fSecsPerTick * ((FLOAT)(qwAppTime.QuadPart));
    m_fElapsedAppTime = fSecsPerTick * ((FLOAT)(qwElapsedAppTime.QuadPart));

    //-----------------------------------------
    // Animate and render a frame
    //-----------------------------------------
#ifndef _DEBUG
    try
    {
#endif
      Process();
      //reset exception count
      processExceptionCount = 0;

#ifndef _DEBUG

    }
    catch (...)
    {
      CLog::Log(LOGERROR, "exception in CApplication::Process()");
      processExceptionCount++;
      //MAX_EXCEPTION_COUNT exceptions in a row? -> bail out
      if (processExceptionCount > MAX_EXCEPTION_COUNT)
      {
        CLog::Log(LOGERROR, "CApplication::Process(), too many exceptions");
        throw;
      }
    }
#endif
    // Frame move the scene
#ifndef _DEBUG
    try
    {
#endif
      if (!m_bStop) FrameMove();
      //reset exception count
      frameMoveExceptionCount = 0;

#ifndef _DEBUG

    }
    catch (...)
    {
      CLog::Log(LOGERROR, "exception in CApplication::FrameMove()");
      frameMoveExceptionCount++;
      //MAX_EXCEPTION_COUNT exceptions in a row? -> bail out
      if (frameMoveExceptionCount > MAX_EXCEPTION_COUNT)
      {
        CLog::Log(LOGERROR, "CApplication::FrameMove(), too many exceptions");
        throw;
      }
    }
#endif

    // Render the scene
#ifndef _DEBUG
    try
    {
#endif
      if (!m_bStop) Render();
      //reset exception count
      renderExceptionCount = 0;

#ifndef _DEBUG

    }
    catch (...)
    {
      CLog::Log(LOGERROR, "exception in CApplication::Render()");
      renderExceptionCount++;
      //MAX_EXCEPTION_COUNT exceptions in a row? -> bail out
      if (renderExceptionCount > MAX_EXCEPTION_COUNT)
      {
        CLog::Log(LOGERROR, "CApplication::Render(), too many exceptions");
        throw;
      }
    }
#endif

  }
  Destroy();

  CLog::Log(LOGNOTICE, "application stopped..." );
  return 0;
}