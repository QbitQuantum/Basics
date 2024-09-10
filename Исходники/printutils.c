void Rvprintf(const char *format, va_list arg)
{
    int i=0, con_num=R_OutputCon;
    Rconnection con;
    va_list argcopy;
    static int printcount = 0;

    if (++printcount > 100) {
	R_CheckUserInterrupt();
	printcount = 0 ;
    }

    do{
      con = getConnection(con_num);
      va_copy(argcopy, arg);
      /* Parentheses added for Fedora with -D_FORTIFY_SOURCE=2 */
      (con->vfprintf)(con, format, argcopy);
      va_end(argcopy);
      con->fflush(con);
      con_num = getActiveSink(i++);
    } while(con_num>0);


}