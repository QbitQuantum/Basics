int main (void)
{
  int i;

  if (_isinf(s_inf()) && _isinf(-s_inf()))
    printf("_isinf() test successful.\n");
  else
    printf("_isinf() test failed.\n");

  for (i = 0; i < 256; ++i)
  {
    if (_isnan(s_nan(i)) != 1)
    {
      printf("_isnan() test failed.\n");
      return 1;
    }
  }
  printf("_isnan() test successful.\n");
  return 0;
}