void bugout( const size_t lineno, const char *fname )
{
   printmsg(0,"Program aborting at line %d in file %s",
              lineno, fname );
   fcloseall();
   exit(69);
} /*bugout */