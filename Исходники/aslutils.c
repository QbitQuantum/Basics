ACPI_STATUS
stroul64 (
    char                    *String,
    UINT32                  Base,
    UINT64                  *RetInteger)
{
    UINT32                  Index;
    UINT32                  Sign;
    UINT64                  ReturnValue = 0;
    ACPI_STATUS             Status = AE_OK;


    *RetInteger = 0;

    switch (Base)
    {
    case 0:
    case 8:
    case 10:
    case 16:

        break;

    default:
        /*
         * The specified Base parameter is not in the domain of
         * this function:
         */
        return (AE_BAD_PARAMETER);
    }

    /* Skip over any white space in the buffer: */

    while (isspace ((int) *String) || *String == '\t')
    {
        ++String;
    }

    /*
     * The buffer may contain an optional plus or minus sign.
     * If it does, then skip over it but remember what is was:
     */
    if (*String == '-')
    {
        Sign = ACPI_SIGN_NEGATIVE;
        ++String;
    }
    else if (*String == '+')
    {
        ++String;
        Sign = ACPI_SIGN_POSITIVE;
    }
    else
    {
        Sign = ACPI_SIGN_POSITIVE;
    }

    /*
     * If the input parameter Base is zero, then we need to
     * determine if it is octal, decimal, or hexadecimal:
     */
    if (Base == 0)
    {
        if (*String == '0')
        {
            if (tolower ((int) *(++String)) == 'x')
            {
                Base = 16;
                ++String;
            }
            else
            {
                Base = 8;
            }
        }
        else
        {
            Base = 10;
        }
    }

    /*
     * For octal and hexadecimal bases, skip over the leading
     * 0 or 0x, if they are present.
     */
    if (Base == 8 && *String == '0')
    {
        String++;
    }

    if (Base == 16 &&
        *String == '0' &&
        tolower ((int) *(++String)) == 'x')
    {
        String++;
    }

    /* Main loop: convert the string to an unsigned long */

    while (*String)
    {
        if (isdigit ((int) *String))
        {
            Index = ((UINT8) *String) - '0';
        }
        else
        {
            Index = (UINT8) toupper ((int) *String);
            if (isupper ((int) Index))
            {
                Index = Index - 'A' + 10;
            }
            else
            {
                goto ErrorExit;
            }
        }

        if (Index >= Base)
        {
            goto ErrorExit;
        }

        /* Check to see if value is out of range: */

        if (ReturnValue > ((ACPI_UINT64_MAX - (UINT64) Index) /
            (UINT64) Base))
        {
            goto ErrorExit;
        }
        else
        {
            ReturnValue *= Base;
            ReturnValue += Index;
        }

        ++String;
    }


    /* If a minus sign was present, then "the conversion is negated": */

    if (Sign == ACPI_SIGN_NEGATIVE)
    {
        ReturnValue = (ACPI_UINT32_MAX - ReturnValue) + 1;
    }

    *RetInteger = ReturnValue;
    return (Status);


ErrorExit:
    switch (Base)
    {
    case 8:

        Status = AE_BAD_OCTAL_CONSTANT;
        break;

    case 10:

        Status = AE_BAD_DECIMAL_CONSTANT;
        break;

    case 16:

        Status = AE_BAD_HEX_CONSTANT;
        break;

    default:

        /* Base validated above */

        break;
    }

    return (Status);
}