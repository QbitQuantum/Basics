int
osdep_setenv(const char *name, const char *value, int overwrite)
{
  if (overwrite || getenv(name) == NULL) {
    _putenv_s(name, value);
  }

  return 0;
}