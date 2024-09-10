void 
NumberFormatRoundTripTest::test(NumberFormat *fmt, const Formattable& value)
{
    fmt->setMaximumFractionDigits(999);
    if(fmt->getDynamicClassID() == DecimalFormat::getStaticClassID()) {
        ((DecimalFormat *)fmt)->setRoundingIncrement(0.0);
    }
    UErrorCode status = U_ZERO_ERROR;
    UnicodeString s, s2, temp;
    if(isDouble(value))
        s = fmt->format(value.getDouble(), s);
    else
        s = fmt->format(value.getLong(), s);

    Formattable n;
    UBool show = verbose;
    if(DEBUG)
        logln(/*value.getString(temp) +*/ " F> " + escape(s));

    fmt->parse(s, n, status);
    failure(status, "fmt->parse");
    if(DEBUG) 
        logln(escape(s) + " P> " /*+ n.getString(temp)*/);

    if(isDouble(n))
        s2 = fmt->format(n.getDouble(), s2);
    else
        s2 = fmt->format(n.getLong(), s2);
    
    if(DEBUG) 
        logln(/*n.getString(temp) +*/ " F> " + escape(s2));

    if(STRING_COMPARE) {
        if (s != s2) {
            errln("*** STRING ERROR \"" + escape(s) + "\" != \"" + escape(s2) + "\"");
            show = TRUE;
        }
    }

    if(EXACT_NUMERIC_COMPARE) {
        if(value != n) {
            errln("*** NUMERIC ERROR");
            show = TRUE;
        }
    }
    else {
        // Compute proportional error
        double error = proportionalError(value, n);

        if(error > MAX_ERROR) {
            errln(UnicodeString("*** NUMERIC ERROR ") + error);
            show = TRUE;
        }

        if (error > max_numeric_error) 
            max_numeric_error = error;
        if (error < min_numeric_error) 
            min_numeric_error = error;
    }

    if (show) {
        errln(/*value.getString(temp) +*/ typeOf(value, temp) + " F> " +
            escape(s) + " P> " + (n.getType() == Formattable::kDouble ? n.getDouble() : (double)n.getLong())
            /*n.getString(temp) */ + typeOf(n, temp) + " F> " +
            escape(s2));
    }
}