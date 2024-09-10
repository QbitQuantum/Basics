static void update_path(void)
{
  char buff1[MAX_PATH*4], *buff2;
  char *path;
  int size, i;

  path = getenv("PATH");
  GetModuleFileNameA(NULL, buff1, sizeof(buff1));
  for (i = strlen(buff1)-1; i > 0; i--)
    if (buff1[i] == '\\') break;
  buff1[i] = 0;

  size = strlen(path) + strlen(buff1) + 3;
  buff2 = malloc(size);
  if (buff2 == NULL) return;

  snprintf(buff2, size, "%s;%s", path, buff1);
  SetEnvironmentVariableA("PATH", buff2);
  free(buff2);
}