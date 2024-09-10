/**
 * Get the job log directory.
 * Ensures that the result is a realpath and that it is underneath the 
 * tt log root.
 */
char* get_job_log_directory(const char* jobid) {
  char* log_dir = get_value(TT_LOG_DIR_KEY);
  if (log_dir == NULL) {
    fprintf(LOGFILE, "Log directory %s is not configured.\n", TT_LOG_DIR_KEY);
    return NULL;
  }
  char *result = concatenate("%s/userlogs/%s", "job log dir", 2, log_dir, 
                             jobid);
  if (result == NULL) {
    fprintf(LOGFILE, "failed to get memory in get_job_log_directory for %s"
            " and %s\n", log_dir, jobid);
  }
  free(log_dir);
  return result;
}