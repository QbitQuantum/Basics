unsigned int
xgetsetbv (void)
{
 _xsetbv (0, 0);
  return _xgetbv (0);
}