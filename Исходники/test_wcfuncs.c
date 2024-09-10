int
main (int argc, char *argv[])
{
  int result = 0;
  wint_t ch;


  for (ch = 0; ch < 128; ++ch)
    {
      if (iswlower (ch))
	{
	  /* Get corresponding upper case character.  */
	  wint_t up = towupper (ch);
	  /* This should have no effect.  */
	  wint_t low  = towlower (ch);

	  if ((ch != low) || (up == ch) || (up == low))
	    {
	      printf ("iswlower/towupper/towlower for character \\%x failed\n", ch);
	      result++;
	    }
	}
      if (iswupper (ch))
	{
	  /* Get corresponding lower case character.  */
	  wint_t low = towlower (ch);
	  /* This should have no effect.  */
	  wint_t up  = towupper (ch);

	  if ((ch != up) || (low == ch) || (up == low))
	    {
	      printf ("iswupper/towlower/towupper for character \\%x failed\n", ch);
	      result++;
	    }
	}
    }

  /* Finally some specific tests.  */
  ch = L'A';
  if (!iswupper (ch) || iswlower (ch))
    {
      printf ("!iswupper/iswlower (L'A') failed\n");
      result++;

    }
  ch = L'a';
  if (iswupper (ch) || !iswlower (ch))
    {
      printf ("iswupper/!iswlower (L'a') failed\n");
      result++;
    }
  if (towlower (L'A') != L'a')
    {
      printf ("towlower(L'A') failed\n");
      result++;
    }
  if (towupper (L'a') != L'A')
    {
      printf ("towupper(L'a') failed\n");
      result++;
    }

  if (result == 0)
    puts ("All test successful!");
  return result != 0;
}