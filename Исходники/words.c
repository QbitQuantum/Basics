void words_shutdown (void) {
   int		  i;
   char		  tmpbuf[128];
   char		  filename[PATH_MAX];
   FILE		  * fp;

   _strtime ( tmpbuf );
   fprintf ( fp_log, "%s FINISH, %d all, %d succ\n", tmpbuf, s_all, s_succ );

   fclose ( fp_log );

   sprintf ( filename, "%s\\%s", wd, "freq.txt" );
   fp = fopen ( filename, "w" );

   fprintf ( fp, ";; ave_rate = %f\n;;\n", ave_rate );
   for ( i = 0; i < N_words; i ++ )
      fprintf ( fp, "%s %d %d %d\n", words[i].word, words[i].succ, words[i].all,
	 words[i].pri );
   fclose ( fp );

   sprintf ( filename, "%s\\%s", wd, "grandt.txt" );
   fp = fopen ( filename, "w" );

   fprintf ( fp, "%d\n%d\n", grand_total_succ, grand_total_all );

   fclose ( fp );
}