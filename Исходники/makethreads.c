void print(void* arg)
{

#if 1
  PutChar((char)arg);
  PutChar('z');
  ThreadExit();
#endif

}