__complex__ double
__cacosh (__complex__ double x)
{
    __complex__ double res;
    int rcls = fpclassify (__real__ x);
    int icls = fpclassify (__imag__ x);

    if (rcls <= FP_INFINITE || icls <= FP_INFINITE)
    {
        if (icls == FP_INFINITE)
        {
            __real__ res = HUGE_VAL;

            if (rcls == FP_NAN)
                __imag__ res = __nan ("");
            else
                __imag__ res = __copysign ((rcls == FP_INFINITE
                                            ? (__real__ x < 0.0
                                               ? M_PI - M_PI_4 : M_PI_4)
                                            : M_PI_2), __imag__ x);
        }
        else if (rcls == FP_INFINITE)
        {
            __real__ res = HUGE_VAL;

            if (icls >= FP_ZERO)
                __imag__ res = __copysign (signbit (__real__ x) ? M_PI : 0.0,
                                           __imag__ x);
            else
                __imag__ res = __nan ("");
        }
        else
        {
            __real__ res = __nan ("");
            __imag__ res = __nan ("");
        }
    }
    else if (rcls == FP_ZERO && icls == FP_ZERO)
    {
        __real__ res = 0.0;
        __imag__ res = __copysign (M_PI_2, __imag__ x);
    }
    else
    {
        __complex__ double y;

        __real__ y = (__real__ x - __imag__ x) * (__real__ x + __imag__ x) - 1.0;
        __imag__ y = 2.0 * __real__ x * __imag__ x;

        y = __csqrt (y);

        if (__real__ x < 0.0)
            y = -y;

        __real__ y += __real__ x;
        __imag__ y += __imag__ x;

        res = __clog (y);

        /* We have to use the positive branch.  */
        if (__real__ res < 0.0)
            res = -res;
    }

    return res;
}