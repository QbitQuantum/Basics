double floor_div(double dividend, double divisor)
{
    if (divisor == 0.0)
        throw std::invalid_argument("division by zero");

    double mod = fmod(dividend, divisor);

    // In float-point arithmetic, dividend - mod is an approximation.
    // Thus after division the div may not be an exact integral value, although
    // it will always be very close to one.
    double div = (dividend - mod) / divisor;
    if (mod != 0)
    {
        // Ensure the remainder has the same sign as the denominator.
        if ((divisor < 0) != (mod < 0))
        {
            mod += divisor;
            div -= 1.0;
        }
    }
    else
    {
        // The remainder is zero, ensure it has the same sign as the denominator.
        mod = _copysign(0.0, divisor);
    }

    // Floor quotient to nearest integral value.
    double quotient(0);
    if (div)
    {
        quotient = floor(div);
        if (div - quotient > 0.5)
            quotient += 1.0;
    }
    else
    {
        // Division result is zero - get the same sign as the true quotient */
        quotient = _copysign(0.0, dividend / divisor);
    }

    return quotient;
}