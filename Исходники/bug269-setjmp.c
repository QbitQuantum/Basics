int
f (void)
{
  static int counter = 0;
  static int way_point1 = 3;
  static int way_point2 = 2;
  int lose = 0;

  if (setjmp (buf1) != 101)
    {
      int a[n_x];		/* reallocate stack space */
      g_counter++;
      p = &a[0];
      if (g_counter < 5)
	longjmp (buf1, 2);
      else if (g_counter == 5)
	longjmp (buf1, 101);
      else
	{
	  _setjmp (buf2);
	  _longjmp (buf1, 101);
	}
    }

  way_point1--;

  if (counter == 0)
    {
      counter++;
      {
	int a[n_x];		/* reallocate stack space */
	g_counter++;
	p = &a[0];
	if (g_counter < 5)
	  longjmp (buf1, 2);
	else if (g_counter == 5)
	  longjmp (buf1, 101);
	else
	  {
	    _setjmp (buf2);
	    _longjmp (buf1, 101);
	  }
      }
    }

  way_point2--;

  if (counter == 1)
    {
      counter++;
      longjmp (buf2, 2);
    }

  lose = !(way_point1 == 0 && way_point2 == 0
	   && g_counter == 6 && counter == 2);

  return lose;
}