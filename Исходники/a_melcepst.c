/* Function Definitions */
static boolean_T b_eml_relop(real_T a, const creal_T b, boolean_T safe_eq)
{
  boolean_T p;
  real_T x;
  real_T b_a;
  real_T b_b;
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  int32_T exponent;
  int32_T b_exponent;
  int32_T c_exponent;
  if ((fabs(a) > 8.9884656743115785E+307) || (fabs(b.re) >
       8.9884656743115785E+307) || (fabs(b.im) > 8.9884656743115785E+307)) {
    x = fabs(a) / 2.0;
    b_a = fabs(b.re / 2.0);
    b_b = fabs(b.im / 2.0);
    if (b_a < b_b) {
      b_a /= b_b;
      b_b *= sqrt(b_a * b_a + 1.0);
    } else if (b_a > b_b) {
      b_b /= b_a;
      b_b = sqrt(b_b * b_b + 1.0) * b_a;
    } else if (rtIsNaN(b_b)) {
    } else {
      b_b = b_a * 1.4142135623730951;
    }
  } else {
    x = fabs(a);
    b_a = fabs(b.re);
    b_b = fabs(b.im);
    if (b_a < b_b) {
      b_a /= b_b;
      b_b *= sqrt(b_a * b_a + 1.0);
    } else if (b_a > b_b) {
      b_b /= b_a;
      b_b = sqrt(b_b * b_b + 1.0) * b_a;
    } else if (rtIsNaN(b_b)) {
    } else {
      b_b = b_a * 1.4142135623730951;
    }
  }

  guard1 = FALSE;
  guard2 = FALSE;
  guard3 = FALSE;
  if ((!safe_eq) && (x == b_b)) {
    guard3 = TRUE;
  } else {
    if (safe_eq) {
      b_a = fabs(b_b / 2.0);
      if ((!rtIsInf(b_a)) && (!rtIsNaN(b_a))) {
        if (b_a <= 2.2250738585072014E-308) {
          b_a = 4.94065645841247E-324;
        } else {
          frexp(b_a, &exponent);
          b_a = ldexp(1.0, exponent - 53);
        }
      } else {
        b_a = rtNaN;
      }

      if ((fabs(b_b - x) < b_a) || (rtIsInf(x) && rtIsInf(b_b) && ((x > 0.0) ==
            (b_b > 0.0)))) {
        p = TRUE;
      } else {
        p = FALSE;
      }

      if (p) {
        guard3 = TRUE;
      }
    }
  }

  if (guard3 == TRUE) {
    x = rt_atan2d_snf(0.0, a);
    b_b = rt_atan2d_snf(b.im, b.re);
    if ((!safe_eq) && (x == b_b)) {
      guard2 = TRUE;
    } else {
      if (safe_eq) {
        b_a = fabs(b_b / 2.0);
        if ((!rtIsInf(b_a)) && (!rtIsNaN(b_a))) {
          if (b_a <= 2.2250738585072014E-308) {
            b_a = 4.94065645841247E-324;
          } else {
            frexp(b_a, &b_exponent);
            b_a = ldexp(1.0, b_exponent - 53);
          }
        } else {
          b_a = rtNaN;
        }

        if ((fabs(b_b - x) < b_a) || (rtIsInf(x) && rtIsInf(b_b) && ((x > 0.0) ==
              (b_b > 0.0)))) {
          p = TRUE;
        } else {
          p = FALSE;
        }

        if (p) {
          guard2 = TRUE;
        }
      }
    }
  }

  if (guard2 == TRUE) {
    x = fabs(a);
    b_b = fabs(b.re);
    if ((!safe_eq) && (x == b_b)) {
      guard1 = TRUE;
    } else {
      if (safe_eq) {
        b_a = b_b / 2.0;
        if ((!rtIsInf(b_a)) && (!rtIsNaN(b_a))) {
          if (b_a <= 2.2250738585072014E-308) {
            b_a = 4.94065645841247E-324;
          } else {
            frexp(b_a, &c_exponent);
            b_a = ldexp(1.0, c_exponent - 53);
          }
        } else {
          b_a = rtNaN;
        }

        if ((fabs(b_b - x) < b_a) || (rtIsInf(x) && rtIsInf(b_b) && ((x > 0.0) ==
              (b_b > 0.0)))) {
          p = TRUE;
        } else {
          p = FALSE;
        }

        if (p) {
          guard1 = TRUE;
        }
      }
    }
  }

  if (guard1 == TRUE) {
    x = 0.0;
    b_b = 0.0;
  }

  return x < b_b;
}