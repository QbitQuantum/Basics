int
main (void)
{
  /* Check that the function exist as a function or as a macro.  */
  (void) iswblank (0);
  /* Check that the isw* functions map WEOF to 0.  */
  ASSERT (!iswblank (e));

  return 0;
}