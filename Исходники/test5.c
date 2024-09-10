int
main()
{
  INIT_EXCEPTIONS();

#ifdef MUST_EXIT
  signal (SIGABRT, catch_abort);
#endif

  set_terminate (terminate_handler);
  
  try
    {
      puts ("Trying something");
      throw (Exception());
    }
  end_try;

}