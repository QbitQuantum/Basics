void Plot::DataSet6 (void)
{
  // Set with only one point to test special cases
  x.Remove();
  y.Remove();
  dy.Remove();
  x  = Vector(1,1, 50.0);
  y  = Vector(1,1, 50.0);
  dy = Vector(1,1,  1.0);
  Recalculate(what);
}