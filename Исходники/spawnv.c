int spawnv(int mode, const char *path, char *const argv[])
{
  return spawnve(mode, path, (char * const *)argv, environ);
}