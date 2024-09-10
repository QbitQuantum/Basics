/**
 * Write the pid of the current process into the pid file.
 * pid_file: Path to pid file where pid needs to be written to
 */
static int write_pid_to_file_as_nm(const char* pid_file, pid_t pid) {
  uid_t user = geteuid();
  gid_t group = getegid();
  if (change_effective_user(nm_uid, nm_gid) != 0) {
    return -1;
  }

  char *temp_pid_file = concatenate("%s.tmp", "pid_file_path", 1, pid_file);

  // create with 700
  int pid_fd = open(temp_pid_file, O_WRONLY|O_CREAT|O_EXCL, S_IRWXU);
  if (pid_fd == -1) {
    fprintf(LOGFILE, "Can't open file %s as node manager - %s\n", temp_pid_file,
           strerror(errno));
    free(temp_pid_file);
    return -1;
  }

  // write pid to temp file
  char pid_buf[21];
  snprintf(pid_buf, 21, "%d", pid);
  ssize_t written = write(pid_fd, pid_buf, strlen(pid_buf));
  close(pid_fd);
  if (written == -1) {
    fprintf(LOGFILE, "Failed to write pid to file %s as node manager - %s\n",
       temp_pid_file, strerror(errno));
    free(temp_pid_file);
    return -1;
  }

  // rename temp file to actual pid file
  // use rename as atomic
  if (rename(temp_pid_file, pid_file)) {
    fprintf(LOGFILE, "Can't move pid file from %s to %s as node manager - %s\n",
        temp_pid_file, pid_file, strerror(errno));
    unlink(temp_pid_file);
    free(temp_pid_file);
    return -1;
  }

  // Revert back to the calling user.
  if (change_effective_user(user, group)) {
	free(temp_pid_file);
    return -1;
  }

  free(temp_pid_file);
  return 0;
}