/* run dlltool on .def file to create import library */
static void
create_implib (struct def_file *def, void *arg)
{
  char *def_name;
  char *lib_name;
  char *p;
  int r;
  static char *argv[] = {NULL,
                         "--as", NULL,
                         "--output-lib", NULL,
                         "--def", NULL,
                         "--dllname", NULL,
                         "-k",
                         NULL};
  fclose (def->f);
  def_name = xmalloc (strlen (def->dllname) + 5);
  lib_name = xmalloc (strlen (def->dllname) + 5);
  dll_to_def_name (def_name, def->dllname);

  p = strrchr (def->dllname, '.');
  if (p)
    {
      *p = '\0';
      sprintf (lib_name, "lib%s.a", def->dllname);
      *p = '.';
    }
  else
    sprintf (lib_name, "lib%s.a", def->dllname);

  if (!keep_case)
    for (p = lib_name + 3; *p; p++)
      *p = tolower (*p);

  argv[0] = dlltool_program;
  argv[2] = as_program;
  argv[4] = lib_name;
  argv[6] = def_name;
  argv[8] = def->dllname;
  r = spawnvp (P_WAIT, argv[0], argv);
  if (r == -1)
    error (1, argv[0]);

  free (lib_name);
  free (def_name);
}