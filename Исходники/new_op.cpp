_GLIBCXX_WEAK_DEFINITION void *
operator new (std::size_t sz) throw (std::bad_alloc)
{
  void *p;

  /* malloc (0) is unpredictable; avoid it.  */
  if (sz == 0)
    sz = 1;
  p = (void *) malloc (sz);
  while (p == 0)
    {
      new_handler handler = __new_handler;
      if (! handler)
#ifdef __EXCEPTIONS
	throw bad_alloc();
#else
        std::abort();
#endif
      handler ();
      p = (void *) malloc (sz);
    }

  return p;
}