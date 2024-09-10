int
main ()
{
  test_strncmp ();

  /* Test comparison with non-BMP characters.  */
  {
    static const UNIT input1[] = { 0xF0, 0x9D, 0x94, 0x9E, 0 };
    static const UNIT input2[] = { 0xEF, 0xBB, 0xBF, 0 };
    ASSERT (U_STRNCMP (input1, input2, 1) > 0);
    ASSERT (U_STRNCMP (input2, input1, 1) < 0);
    ASSERT (U_STRNCMP (input1, input2, 2) > 0);
    ASSERT (U_STRNCMP (input2, input1, 2) < 0);
    ASSERT (U_STRNCMP (input1, input2, 3) > 0);
    ASSERT (U_STRNCMP (input2, input1, 3) < 0);
    ASSERT (U_STRNCMP (input1, input2, 4) > 0);
    ASSERT (U_STRNCMP (input2, input1, 4) < 0);
    ASSERT (U_STRNCMP (input1, input2, 5) > 0);
    ASSERT (U_STRNCMP (input2, input1, 5) < 0);
    ASSERT (U_STRNCMP (input1, input2, 1000000) > 0);
    ASSERT (U_STRNCMP (input2, input1, 1000000) < 0);
  }

  return 0;
}