int spawnvp(int mode, const char *path, char *const argv[])
{
  return spawnvpe(mode, path, (char * const *)argv, environ);
}