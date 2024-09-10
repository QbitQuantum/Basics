void 
IntlTestNumberFormat::tryIt(double aNumber)
{
    const int32_t DEPTH = 10;
    Formattable number[DEPTH];
    UnicodeString string[DEPTH];

    int32_t numberMatch = 0;
    int32_t stringMatch = 0;
    UnicodeString errMsg;
    int32_t i;
    for (i=0; i<DEPTH; ++i)
    {
        errMsg.truncate(0); // if non-empty, we failed this iteration
        UErrorCode status = U_ZERO_ERROR;
        string[i] = "(n/a)"; // "format was never done" value
        if (i == 0) {
            number[i].setDouble(aNumber);
        } else {
            fFormat->parse(string[i-1], number[i], status);
            if (U_FAILURE(status)) {
                number[i].setDouble(1234.5); // "parse failed" value
                errMsg = "**** FAIL: Parse of " + prettify(string[i-1]) + " failed.";
                --i; // don't show empty last line: "1234.5 F> (n/a) P>"
                break;
            }
        }
        // Convert from long to double
        if (number[i].getType() == Formattable::kLong)
            number[i].setDouble(number[i].getLong());
        else if (number[i].getType() == Formattable::kInt64)
            number[i].setDouble((double)number[i].getInt64());
        else if (number[i].getType() != Formattable::kDouble)
        {
            errMsg = ("**** FAIL: Parse of " + prettify(string[i-1])
                + " returned non-numeric Formattable, type " + UnicodeString(formattableTypeName(number[i].getType()))
                + ", Locale=" + UnicodeString(fLocale.getName())
                + ", longValue=" + number[i].getLong());
            break;
        }
        string[i].truncate(0);
        fFormat->format(number[i].getDouble(), string[i]);
        if (i > 0)
        {
            if (numberMatch == 0 && number[i] == number[i-1])
                numberMatch = i;
            else if (numberMatch > 0 && number[i] != number[i-1])
            {
                errMsg = ("**** FAIL: Numeric mismatch after match.");
                break;
            }
            if (stringMatch == 0 && string[i] == string[i-1])
                stringMatch = i;
            else if (stringMatch > 0 && string[i] != string[i-1])
            {
                errMsg = ("**** FAIL: String mismatch after match.");
                break;
            }
        }
        if (numberMatch > 0 && stringMatch > 0)
            break;
    }
    if (i == DEPTH)
        --i;

    if (stringMatch > 2 || numberMatch > 2)
    {
        errMsg = ("**** FAIL: No string and/or number match within 2 iterations.");
    }

    if (errMsg.length() != 0)
    {
        for (int32_t k=0; k<=i; ++k)
        {
            logln((UnicodeString)"" + k + ": " + number[k].getDouble() + " F> " +
                  prettify(string[k]) + " P> ");
        }
        errln(errMsg);
    }
}