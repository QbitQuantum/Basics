void *
exceptionedThread(void * arg)
{
  int dummy = 0x1;

  set_terminate(&terminateFunction);
  assert(set_terminate(&terminateFunction) == &terminateFunction);

  throw dummy;

  return (void *) 2;
}