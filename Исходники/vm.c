static void write(WrenVM* vm, const char* text)
{
  printf("%s", text);
  fflush(stdout);
}