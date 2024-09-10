nsresult WinProcMon::QuerySystemLoad(float* load_percent)
{
  *load_percent = 0;

  if (mQuery == 0) {
    return NS_ERROR_FAILURE;
  }

  // Update all counters associated with this query object.
  PDH_STATUS status = PdhCollectQueryData(mQuery);

  if (status != ERROR_SUCCESS) {
    LOG(("PdhCollectQueryData error = %X", status));
    return NS_ERROR_FAILURE;
  }

  PDH_FMT_COUNTERVALUE counter;
  // maximum is 100% regardless of CPU core count.
  status = PdhGetFormattedCounterValue(
               mCounter,
               PDH_FMT_DOUBLE,
               (LPDWORD)NULL,
               &counter);

  if (ERROR_SUCCESS != status ||
      // There are multiple success return values.
      !IsSuccessSeverity(counter.CStatus)) {
    LOG(("PdhGetFormattedCounterValue error"));
    return NS_ERROR_FAILURE;
  }

  // The result is a percent value, reduce to match expected scale.
  *load_percent = (float)(counter.doubleValue / 100.0f);
  return NS_OK;
}