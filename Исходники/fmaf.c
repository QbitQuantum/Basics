int main(int argc, char *argv[])
{
  float x = 0.0;
  if (argv) x = fmaf((float) argc, (float) argc, (float) argc);
  return 0;
}