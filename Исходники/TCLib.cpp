DATE GetLocalVariantDate()
{
  // Get the current date/time in Universal Coordinated Time (UCT)
  SYSTEMTIME st;
  GetLocalTime(&st);

  // Clear the time fields (00:00 midnight by convention)
  st.wHour = 0;
  st.wMinute = 0;
  st.wSecond = 0;
  st.wMilliseconds = 0;

  // Convert the date to VariantTime
  DATE time = 0;
  _VERIFYE(SystemTimeToVariantTime(&st, &time));
  return time;
}