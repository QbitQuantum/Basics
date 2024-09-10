bool TSecTm::GetTmStruct(const uint& AbsSec, struct tm& Tm) {
  const time_t TimeT = time_t(AbsSec);
  #if defined(GLib_MSC)
  return _gmtime64_s(&Tm, &TimeT) == 0;
  #elif defined(GLib_BCB)
  Tm=*gmtime(&TimeT); return true;
  #else
  return gmtime_r(&TimeT, &Tm) != NULL;
  #endif
}