void
foo (struct S *x)
{
  if (x->a != C || x->b != D)
    abort ();
}