/** Post job result information to Nagios 3.x.
 *
 * Nagios 3.x uses a filesystem-based method of posting results. Results are
 * written to a temporary file. Once the temp file is closed, it's moved into
 * the Nagios results queue directory, and a marker file of the same name, but
 * with a ".ok" suffice, is created. This marker file tells Nagios that the 
 * results file is complete and ready to be processed.
 *
 * Nagios writes the first half of the results file in a temporary directory, 
 * and allows the child check process to finish it and move it to the results
 * queue directory. DNX foregoes the temporarly file and writes the results 
 * file directly into the queue directory, and then creates the marker file.
 *
 * SECURITY NOTE: Nagios creates the results file in a secure manner by 
 * setting the umask to mask off ALL rights from anyone but the owner of the 
 * file (Nagios). DNX doesn't have the luxury of being able to manipulate the
 * umask because DNX check results are posted in a secondary thread, which is
 * not allowed to manipulate the umask because it would cause a race condition
 * with the main thread in Nagios.
 *
 * @param[in] svc - the nagios service to which the results belong.
 * @param[in] check_type - nagios 3.x check type value.
 * @param[in] check_options - nagios 3.x bit-wise check options.
 * @param[in] schedule - boolean; nagios 3.x schedule flag.
 * @param[in] reschedule - boolean; nagios 3.x reschedule flag.
 * @param[in] start_time - the check start time in seconds.
 * @param[in] finish_time - the check finish time in seconds.
 * @param[in] early_timeout - boolean; true (!0) means the service timed out.
 * @param[in] exited_ok - boolean; true (!0) if the external check exited ok.
 * @param[in] res_code - the check result code.
 * @param[in] res_data - the check result data.
 *
 * @return Zero on success, or a non-zero error value.
 *
 * @todo This routine should be in nagios code.
 */
static int nagios3xPostResult(service * svc, int check_type,
      int check_options, int schedule, int reschedule,
      time_t start_time, time_t finish_time, int early_timeout,
      int exited_ok, int res_code, char * res_data)
{
   char * escaped_res_data;
   char * filename;
   FILE * fp = 0;
   int fd;

   // a nagios 3.x global variable
   extern char * temp_path;

   // a nagios 3.x core function
   if ((escaped_res_data = escape_newlines(res_data)) == 0)
      return DNX_ERR_MEMORY;

   // open a file in the check results path for storing check results
   // path length + 'checkXXXXXX' (11) + '/' (1) + '.ok' (3) + null (1)
   if ((filename = (char *)xmalloc(strlen(temp_path) 
         + 11 + 1 + 3 + 1)) == 0)
   {
      free(escaped_res_data); // allocated by nagios - use free
      return DNX_ERR_MEMORY;
   }
   sprintf(filename, "%s/checkXXXXXX", temp_path);
   if ((fd = mkstemp(filename)) < 0
         || (fp = fdopen(fd, "w")) == 0)
   {
      xfree(filename);
      free(escaped_res_data); // allocated by nagios - use free
      if (fd >= 0) close(fd);
      return DNX_ERR_OPEN;
   }

   // write check results to the queue file
   fprintf(fp, "### Active Check Result File ###\n");
   fprintf(fp, "file_time=%lu\n\n", (unsigned long)start_time);
   fprintf(fp, "### Nagios Service Check Result ###\n");
   fprintf(fp, "# Time: %s", ctime(&start_time));
   fprintf(fp, "host_name=%s\n", svc->host_name);
   fprintf(fp, "service_description=%s\n", svc->description);
   fprintf(fp, "check_type=%d\n", check_type);
   fprintf(fp, "check_options=%d\n", check_options);
   fprintf(fp, "scheduled_check=%d\n", schedule);
   fprintf(fp, "reschedule_check=%d\n", reschedule);
   fprintf(fp, "latency=%f\n", svc->latency);
   fprintf(fp, "start_time=%lu.0\n", (unsigned long)start_time);
   fprintf(fp, "finish_time=%lu.%lu\n", (unsigned long)finish_time);
   fprintf(fp, "early_timeout=%d\n", early_timeout);
   fprintf(fp, "exited_ok=%d\n", exited_ok);
   fprintf(fp, "return_code=%d\n", res_code);
   fprintf(fp, "output=%s\n", escaped_res_data);

   fclose(fp);

   free(escaped_res_data); // allocated by nagios - use free

   nagios3xMoveCheckResultToQueue(filename);

   xfree(filename);

   return 0;
}