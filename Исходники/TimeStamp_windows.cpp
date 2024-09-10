static void
InitThresholds()
{
  DWORD timeAdjustment = 0, timeIncrement = 0;
  BOOL timeAdjustmentDisabled;
  GetSystemTimeAdjustment(&timeAdjustment,
                          &timeIncrement,
                          &timeAdjustmentDisabled);

  LOG(("TimeStamp: timeIncrement=%d [100ns]", timeIncrement));

  if (!timeIncrement) {
    timeIncrement = kDefaultTimeIncrement;
  }

  // Ceiling to a millisecond
  // Example values: 156001, 210000
  DWORD timeIncrementCeil = timeIncrement;
  // Don't want to round up if already rounded, values will be: 156000, 209999
  timeIncrementCeil -= 1;
  // Convert to ms, values will be: 15, 20
  timeIncrementCeil /= 10000;
  // Round up, values will be: 16, 21
  timeIncrementCeil += 1;
  // Convert back to 100ns, values will be: 160000, 210000
  timeIncrementCeil *= 10000;

  // How many milli-ticks has the interval rounded up
  LONGLONG ticksPerGetTickCountResolutionCeiling =
    (int64_t(timeIncrementCeil) * sFrequencyPerSec) / 10000LL;

  // GTC may jump by 32 (2*16) ms in two steps, therefor use the ceiling value.
  sGTCResolutionThreshold =
    LONGLONG(kGTCTickLeapTolerance * ticksPerGetTickCountResolutionCeiling);

  sHardFailureLimit = ms2mt(kHardFailureLimit);
  sFailureFreeInterval = ms2mt(kFailureFreeInterval);
  sFailureThreshold = ms2mt(kFailureThreshold);
}