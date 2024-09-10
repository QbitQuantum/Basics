/**
 * Return the current amount of time on the clock.
 * This is the total amout of time that has elapsed
 * between Start() and Stop() pairs since the last
 * Reset().
 */
inline float StopwatchBase::GetTime() const
{
  if (running) return (elapsedTime + diffTime());
  else return (elapsedTime);
}