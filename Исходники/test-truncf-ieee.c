int
main ()
{
  /* See IEEE 754, section 6.3:
       "the sign of the result of the round floating-point number to
        integral value operation is the sign of the operand. These rules
        shall apply even when operands or results are zero or infinite."  */

  /* Zero.  */
  ASSERT (!signbit (truncf (0.0f)));
  ASSERT (!!signbit (truncf (minus_zerof)) == !!signbit (minus_zerof));
  /* Positive numbers.  */
  ASSERT (!signbit (truncf (0.3f)));
  ASSERT (!signbit (truncf (0.7f)));
  /* Negative numbers.  */
  ASSERT (!!signbit (truncf (-0.3f)) == !!signbit (minus_zerof));
  ASSERT (!!signbit (truncf (-0.7f)) == !!signbit (minus_zerof));

  /* [MX] shaded specification in POSIX.  */

  /* NaN.  */
  ASSERT (isnanf (truncf (NaNf ())));
  /* Infinity.  */
  ASSERT (truncf (Infinityf ()) == Infinityf ());
  ASSERT (truncf (- Infinityf ()) == - Infinityf ());

  return 0;
}