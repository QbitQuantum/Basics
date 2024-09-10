{
  return 0;
}

int
main (int argc, char **argv _GL_UNUSED)
{
  float (*my_floorf) (float) = argc ? floorf : dummy;

  /* See IEEE 754, section 6.3:
       "the sign of the result of the round floating-point number to
        integral value operation is the sign of the operand. These rules
        shall apply even when operands or results are zero or infinite."  */

  /* Zero.  */
  ASSERT (!signbit (my_floorf (0.0f)));
  ASSERT (!!signbit (my_floorf (minus_zerof)) == !!signbit (minus_zerof));
  /* Positive numbers.  */
  ASSERT (!signbit (my_floorf (0.3f)));
  ASSERT (!signbit (my_floorf (0.7f)));
  /* Negative numbers.  */
  ASSERT (!!signbit (my_floorf (-0.3f)) == !!signbit (minus_zerof));
  ASSERT (!!signbit (my_floorf (-0.7f)) == !!signbit (minus_zerof));

  /* [MX] shaded specification in POSIX.  */

  /* NaN.  */
  ASSERT (isnanf (floorf (NaNf ())));
  /* Infinity.  */
  ASSERT (floorf (Infinityf ()) == Infinityf ());
  ASSERT (floorf (- Infinityf ()) == - Infinityf ());