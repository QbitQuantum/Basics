sl_def(t_main, void)
{
  double x = slr_get(x)[0];
  double t1 = tgamma(x);
  float t2 = tgammaf(x);
  output_float(x, 1, 4);
  output_char(' ', 1);
  output_float(t1, 1, 4);
  output_char(' ', 1);
  output_float(t2, 1, 4);
  output_char('\n', 1);
}