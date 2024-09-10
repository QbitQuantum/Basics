vtime_t to_utc(vtime_t _time)
{
  __int64 local = (__int64)(_time * 10000000 + epoch_adj);
  __int64 utc;

  LocalFileTimeToFileTime((FILETIME*)&local, (FILETIME*)&utc);
  return vtime_t(utc - epoch_adj) / 10000000;
}