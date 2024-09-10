void
fn0 (int n)
{
  p = __builtin_alloca_with_align (n, 6); /* { dg-error "39:must be a constant integer" } */

  r += __builtin_isfinite (0); /* { dg-error "28:non-floating-point argument in call" } */
  r += __builtin_isinf (0); /* { dg-error "25:non-floating-point argument in call" } */
  r += __builtin_isinf_sign (0); /* { dg-error "30:non-floating-point argument in call" } */
  r += __builtin_isnan (0); /* { dg-error "25:non-floating-point argument in call" } */
  r += __builtin_isnormal (0); /* { dg-error "28:non-floating-point argument in call" } */
  r += __builtin_signbit (0); /* { dg-error "27:non-floating-point argument in call" } */

  r += __builtin_isgreater (0, 0); /* { dg-error "8:non-floating-point arguments in call to function" } */
  r += __builtin_isgreaterequal (0, 0); /* { dg-error "8:non-floating-point arguments in call to function" } */
  r += __builtin_isless (0, 0); /* { dg-error "8:non-floating-point arguments in call to function" } */
  r += __builtin_islessequal (0, 0); /* { dg-error "8:non-floating-point arguments in call to function" } */
  r += __builtin_islessgreater (0, 0); /* { dg-error "8:non-floating-point arguments in call to function" } */
  r += __builtin_isunordered (0, 0); /* { dg-error "8:non-floating-point arguments in call to function" } */

  r += __builtin_fpclassify (1, 2, n, 4, 5, n); /* { dg-error "36:non-const integer argument 3 in call" } */
  r += __builtin_fpclassify (1, 2, 3, 4, 5, 6); /* { dg-error "45:non-floating-point argument in call" } */

  d = __builtin_assume_aligned (p, n, p); /* { dg-error "39:non-integer argument 3 in call" } */

  b = __builtin_add_overflow (n, *d, &r); /* { dg-error "34:argument 2 in call to function" } */
  b = __builtin_add_overflow (n, 5, d); /* { dg-error "37:argument 3 in call" } */
  b = __builtin_sub_overflow (n, *d, &r); /* { dg-error "34:argument 2 in call to function" } */
  b = __builtin_sub_overflow (n, 5, d); /* { dg-error "37:argument 3 in call" } */
  b = __builtin_mul_overflow (n, *d, &r); /* { dg-error "34:argument 2 in call to function" } */
  b = __builtin_mul_overflow (n, 5, d); /* { dg-error "37:argument 3 in call" } */
}