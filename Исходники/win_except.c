void pony_throw()
{
  //Continuable exception with no arguments. RaiseException involves a kernel
  //mode transition.
  RaiseException(PONY_EXCEPTION_CLASS, 0, 0, NULL);

  //Never reaches here, since exceptions are always handled.
  abort();
}