int filebkup( const char *input )
{
   char fdrive[FILENAME_MAX];
   char fpath[FILENAME_MAX];
   char fname[FILENAME_MAX];
   char ftype[FILENAME_MAX];
   char backup[FILENAME_MAX];

   if ( !bflag[F_BACKUP] )    /* Are we to not back it up?            */
      return 1;               /* Yes --> Report we did not            */

#ifdef __TURBOC__
   fnsplit( input, fdrive, fpath, fname, ftype );

   if ( E_backup == NULL )
      strcpy(ftype, ".bak" );
   else if ( *E_backup == '.' )
      strcpy( ftype, E_backup );
   else {
      *ftype = '.';
      strcpy(  ftype + 1 , E_backup );
   } /* else */

   fnmerge( backup, fdrive, fpath, fname, ftype );
#else

   if ( E_backup == NULL )
      E_backup = ".bak";

   _splitpath( (char *) input , fdrive, fpath, fname, ftype );
   _makepath( backup , fdrive, fpath, fname, E_backup );
#endif /* __TURBOC__ */

   REMOVE( backup );

   if (rename( input, backup ))
   {
      printerr( backup );
      printmsg(1,"Unable to rename %s to %s", input, backup );
      return 1;

   } /* if (rename( input, backup )) */
   else
      return 0;

} /* filebkup */