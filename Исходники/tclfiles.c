static int tcl_rmdir(ClientData cd, Tcl_Interp *irp,
                     int argc, char *argv[])
{
  FILE *fdb;
  filedb_entry *fdbe;
  char *s = NULL, *t, *d, *p;

  BADARGS(2, 2, " dir");

  malloc_strcpy(s, argv[1]);
  if (s[strlen(s) - 1] == '/')
    s[strlen(s) - 1] = 0;
  p = strrchr(s, '/');
  if (p == NULL) {
    p = s;
    d = "";
  } else {
    *p = 0;
    p++;
    d = s;
  }

  fdb = filedb_open(d, 0);
  if (!fdb) {
    Tcl_AppendResult(irp, "1", NULL);
    my_free(s);
    return TCL_OK;
  }
  filedb_readtop(fdb, NULL);
  fdbe = filedb_matchfile(fdb, ftell(fdb), p);

  if (!fdbe) {
    Tcl_AppendResult(irp, "1", NULL);
    filedb_close(fdb);
    my_free(s);
    return TCL_OK;
  }
  if (!(fdbe->stat & FILE_DIR)) {
    Tcl_AppendResult(irp, "1", NULL);
    filedb_close(fdb);
    free_fdbe(&fdbe);
    my_free(s);
    return TCL_OK;
  }
  /* Erase '.filedb' and '.files' if they exist */
  t = nmalloc(strlen(dccdir) + strlen(d) + strlen(p) + 11);
  sprintf(t, "%s%s/%s/.filedb", dccdir, d, p);
  unlink(t);
  sprintf(t, "%s%s/%s/.files", dccdir, d, p);
  unlink(t);
  sprintf(t, "%s%s/%s", dccdir, d, p);
  my_free(s);
  if (rmdir(t) == 0) {
    filedb_delfile(fdb, fdbe->pos);
    filedb_close(fdb);
    free_fdbe(&fdbe);
    my_free(t);
    Tcl_AppendResult(irp, "0", NULL);
    return TCL_OK;
  }
  my_free(t);
  free_fdbe(&fdbe);
  filedb_close(fdb);
  Tcl_AppendResult(irp, "1", NULL);
  return TCL_OK;
}