/**
 * Helper: try to prevent the <b>sz</b> bytes at <b>mem</b> from being swapped
 * to disk.  Return 0 on success or if the facility is not available on this
 * OS; return -1 on failure.
 */
static int
lock_mem(void *mem, size_t sz)
{
#ifdef _WIN32
  return VirtualLock(mem, sz) ? 0 : -1;
#elif defined(HAVE_MLOCK)
  return mlock(mem, sz);
#else
  (void) mem;
  (void) sz;

  return 0;
#endif
}