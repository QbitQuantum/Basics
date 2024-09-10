static int GM_CDECL gmfTime(gmThread * a_thread)
{
#ifdef IS64BIT // Compatible with 64bit OS
  __time32_t t;
  _time32(&t);
  GM_ASSERT(sizeof(t) <= sizeof(gmint));
  a_thread->PushInt(t);
  return GM_OK;
#else
  time_t t;
  time(&t);
  GM_ASSERT(sizeof(time_t) <= sizeof(gmptr));
  a_thread->PushInt(t);
  return GM_OK;
#endif
}