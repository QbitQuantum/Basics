 PosibErr<const char *> operator() (char c)
 {
   char buf2[2] = {c, 0};
   return operator()(ParmString(buf2,1));
 }