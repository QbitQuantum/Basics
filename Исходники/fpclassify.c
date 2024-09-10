int main(int argc, char *argv[])
{
  double x = 0.0;
  if (argv) x = fpclassify((double) argc);
  return 0;
}