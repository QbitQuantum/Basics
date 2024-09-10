/*--------------------------------------------------------------------------*/
void
mtarch_init(void)
{
#if defined(_WIN32) || defined(__CYGWIN__)

  main_fiber = ConvertThreadToFiber(NULL);

#endif /* _WIN32 || __CYGWIN__ */
}