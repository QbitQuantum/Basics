//
// GetCurrentGameTime
// Purpose: Retrieves the current game time in high resolution seconds
//
float GetCurrentGameTime( void )
{
  LARGE_INTEGER currentTime;
  QueryPerformanceCounter( &currentTime );
  return (float)(currentTime.QuadPart) / (float)(FREQUENCY.QuadPart);
}