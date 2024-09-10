int
main ()
{
  DECL_LONG_DOUBLE_ROUNDING

  BEGIN_LONG_DOUBLE_ROUNDING ();

  /* See IEEE 754, section 6.3:
       "the sign of the result of the round floating-point number to
        integral value operation is the sign of the operand. These rules
        shall apply even when operands or results are zero or infinite."  */

  /* Zero.  */
  ASSERT (!signbit (truncl (0.0L)));
  ASSERT (!!signbit (truncl (minus_zerol)) == !!signbit (minus_zerol));
  /* Positive numbers.  */
  ASSERT (!signbit (truncl (0.3L)));
  ASSERT (!signbit (truncl (0.7L)));
  /* Negative numbers.  */
  ASSERT (!!signbit (truncl (-0.3L)) == !!signbit (minus_zerol));
  ASSERT (!!signbit (truncl (-0.7L)) == !!signbit (minus_zerol));

  /* [MX] shaded specification in POSIX.  */

  /* NaN.  */
  ASSERT (isnanl (truncl (NaNl ())));
  /* Infinity.  */
  ASSERT (truncl (Infinityl ()) == Infinityl ());
  ASSERT (truncl (- Infinityl ()) == - Infinityl ());

  return 0;
}