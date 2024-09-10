int
main ()
{
  test_strncmp ();

  /* Test comparison with non-BMP characters.  */
  {
    static const UNIT input1[] = { 0x1D51F, 0 };
    static const UNIT input2[] = { 0xFEFF, 0 };
    ASSERT (U_STRNCMP (input1, input2, 1) > 0);
    ASSERT (U_STRNCMP (input2, input1, 1) < 0);
    ASSERT (U_STRNCMP (input1, input2, 2) > 0);
    ASSERT (U_STRNCMP (input2, input1, 2) < 0);
    ASSERT (U_STRNCMP (input1, input2, 1000000) > 0);
    ASSERT (U_STRNCMP (input2, input1, 1000000) < 0);
  }

  return 0;
}