/**
 * The function converts the character string into double. 
 *
 * @param aStr              [TInt8*] String Value.
 *
 * @return                  The function returns double conversion of the string value if its successfull. 
 *                          Otherwise, zero is returned.
 */
TReal64 ALGO_ATOF(const TInt8* aStr)
    {
    TReal64 number;
    TInt32 exponent;
    TInt32 negative;
    TInt8 *p = (TInt8 *) aStr;
    TReal64 p10;
    TInt32 n;
    TInt32 num_digits;
    TInt32 num_decimals;

    // Skip leading whitespace
    while (IsSpace(*p)) 
        {
        p++;
        }

    // Handle optional sign
    negative = 0;
    switch (*p) 
    {             
    case '-': 
        negative = 1; // Fall through to increment position
    case '+': 
        p++;
    }

    number = 0.;
    exponent = 0;
    num_digits = 0;
    num_decimals = 0;

    // Process string of digits
    while (IsDigit(*p))
        {
        number = number * 10. + (*p - '0');
        p++;
        num_digits++;
        }

    // Process decimal part
    if (*p == '.') 
        {
        p++;
        while (IsDigit(*p))
            {
            number = number * 10. + (*p - '0');
            p++;
            num_digits++;
            num_decimals++;
            }
        exponent -= num_decimals;
        }

    if (num_digits == 0)
        {
        return 0.0;
        }

    // Correct for sign
    if (negative) 
        {
        number = -number;
        }

    // Process an exponent string
    if (*p == 'e' || *p == 'E') 
        {
        // Handle optional sign
        negative = 0;
        switch(*++p) 
            {   
            case '-': 
                negative = 1;   // Fall through to increment pos
            case '+': 
                p++;
            }

    // Process string of digits
    n = 0;
    while (IsDigit(*p)) 
    {   
      n = n * 10 + (*p - '0');
      p++;
    }

    if (negative) 
      exponent -= n;
    else
      exponent += n;
    }

    // Scale the result
    p10 = 10.;
    n = exponent;
    if (n < 0) 
        {
        n = -n;
        }

    while (n) 
        {
        if (n & 1) 
            {   
            if (exponent < 0)
                {
                number /= p10;
                }
            else
                {
                number *= p10;
                }
            }
        n >>= 1;
        p10 *= p10;
        }

    return number;
    }