int main(int argc, char *argv[])
{
  long double x = 0.0;
  if (argv) x = llrintl((long double) argc);
  return 0;
}