 /* system calls which differ in signature across OS's in ways that C++ cannot deal with */
 extern int SOCK_getsockopt(int  s, int level, int optname, void *optval, GETSOCKOPT_LENGTH_T *optlen) {
   return getsockopt(s, level, optname, optval, (void *)optlen);
 }