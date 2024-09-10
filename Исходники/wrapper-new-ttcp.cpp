/*
 *                    N W R I T E
 */
int
Nwrite (ACE_SOCK_Stream &s, void *buf, int count)
{
  numCalls++;
  return s.send (buf, count);
}