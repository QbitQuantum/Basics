unsigned int
_timeout(void *arg)
{
   int s = (int)(uintptr_t)arg;
   Sleep(s * 1000);
   _Exit(-1);
   _endthreadex(0);
   return 0;
}