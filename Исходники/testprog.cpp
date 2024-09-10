int main()
{
#ifdef __MSVC_DEBUG__
  InitLeakTest();
#endif

  SimpleThread t;
  char *message1 = "The quick brown fox jumps over the lazy dog";

  // Test the parameter passing to create function
  gxThread_t *tptr = t.CreateThread((void *)message1);

  // Wait for the thread to exit
  t.sSleep(1); 

  delete tptr; // Prevent memory leaks
  return 0; // Exit the process
}