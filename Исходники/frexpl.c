int main(int argc, char *argv[])
{
  long double x = 0.0;
  int i = 0;

  if (argv) x = frexpl((long double) argc, &i);
  return 0;
}