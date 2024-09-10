bool
F::m_fn2 ()
{
  B a (0);
  if (a)
    if (_setjmp (what_.cond_))
      return 0;
    else
      D ();
  A b;
}