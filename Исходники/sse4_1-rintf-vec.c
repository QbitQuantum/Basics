TEST (void)
{
  float a[NUM];
  float r[NUM];
  int i;

  init_src (a);

  for (i = 0; i < NUM; i++)
    r[i] = rintf (a[i]);

  /* check results:  */
  for (i = 0; i < NUM; i++)
    if (r[i] != rintf (a[i]))
      abort();
}