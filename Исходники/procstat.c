int is_pct_stat(char *iname)
{
   /* Check the converse first. This solves the problem of a user 
      entering both .pct. and .raw. */
   if ( StrStr(iname, ".raw.") )
      return(0);

   if ( StrStr(iname, ".pct.") )
      return(1);

   return(0);
}