int main(int argc, char **argv) {
  char python_bin[PATH_MAX + 1], argv0_bin[PATH_MAX + 1], *p, *q;
  char prog_py[PATH_MAX + 1];
  const char *moreargv[ARGV_MAX + 1];
  int i;
  (void)argc;
  p = argv[0];
  q = NULL;
  while (*p != '\0') {
    if (*p++ == FILE_SEP) q = p;
  }
  if (q == NULL) {  // Try to find argv[0] on $PATH.
    p = argv[0];
    strncpy(argv0_bin, p, sizeof argv0_bin);
    q = NULL;
    while (*p != '\0') {
      if (*p++ == '.') q = p;
    }
    if (q == NULL) {
      argv0_bin[sizeof argv0_bin - 5] = '\0';
      strcat(argv0_bin, ".exe");
    } else {
      argv0_bin[sizeof argv0_bin - 1] = '\0';
    }
    find_on_path(argv0_bin, python_bin);
  } else {  // Put dirname(argv[0]) to python_bin.
    p = argv[0];
    --q;
    if (q - p > PATH_MAX) {
      q = p + PATH_MAX;
    }
    strncpy(python_bin, p, q - p);
    python_bin[q - p] = '\0';
  }

  if (python_bin[0] == '\0') {
    python_bin[0] = '.';
    python_bin[1] = '\0';
  }
  strcpy(prog_py, python_bin);

  i = strlen(python_bin);
  if (i + strlen(python_exe) > PATH_MAX) {
    i = PATH_MAX - strlen(python_exe);
  }
  python_bin[i] = FILE_SEP;
  strcpy(python_bin + i + 1, python_exe);

  i = strlen(prog_py);
  if (i + strlen(pdfsizeopt_py) > PATH_MAX) {
    i = PATH_MAX - strlen(pdfsizeopt_py);
  }
  prog_py[i] = FILE_SEP;
  strcpy(prog_py + i + 1, pdfsizeopt_py);

  moreargv[0] = "python26";
  moreargv[1] = prog_py;
  for (i = 1; argv[i] != NULL; ++i) {
    moreargv[i + 1] = argv[i];
  }
  moreargv[i + 1] = NULL;
  

  // execv(...) and P_OVERLAY don't work well in wine-1.2.2 and Windows XP,
  // because they make this process return before the started process finishes.
  i = spawnv(P_WAIT, python_bin, moreargv);
  if (i < 0) {
    fprintf(stderr, "error: could not start %s: %s\n",
            python_bin, strerror(errno));
    return 120;
  }
  return i;
}