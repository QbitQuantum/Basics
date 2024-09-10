int
main ()
{

/* IoctlSocket source code */
 int socket;
 int flags = IoctlSocket(socket, FIONBIO, (long)1);

  ;
  return 0;
}