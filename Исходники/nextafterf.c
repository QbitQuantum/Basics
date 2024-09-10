int main(int argc, char *argv[])
{
  float x = 0.0;
  if (argv) x = nextafterf((float) argc, (float) argc);
  return 0;
}