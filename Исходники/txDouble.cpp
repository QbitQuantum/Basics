/*
 * Converts the value of the given double to a String, and places
 * The result into the destination String.
 * @return the given dest string
 */
void Double::toString(double aValue, nsAString& aDest)
{

    // check for special cases

    if (isNaN(aValue)) {
        aDest.AppendLiteral("NaN");
        return;
    }
    if (isInfinite(aValue)) {
        if (aValue < 0)
            aDest.Append(PRUnichar('-'));
        aDest.AppendLiteral("Infinity");
        return;
    }

    // Mantissa length is 17, so this is plenty
    const int buflen = 20;
    char buf[buflen];

    PRIntn intDigits, sign;
    char* endp;
    PR_dtoa(aValue, 0, 0, &intDigits, &sign, &endp, buf, buflen - 1);

    // compute length
    PRInt32 length = endp - buf;
    if (length > intDigits) {
        // decimal point needed
        ++length;
        if (intDigits < 1) {
            // leading zeros, -intDigits + 1
            length += 1 - intDigits;
        }
    }
    else {
        // trailing zeros, total length given by intDigits
        length = intDigits;
    }
    if (aValue < 0)
        ++length;
    // grow the string
    PRUint32 oldlength = aDest.Length();
    if (!EnsureStringLength(aDest, oldlength + length))
        return; // out of memory
    nsAString::iterator dest;
    aDest.BeginWriting(dest).advance(PRInt32(oldlength));
    if (aValue < 0) {
        *dest = '-'; ++dest;
    }
    int i;
    // leading zeros
    if (intDigits < 1) {
        *dest = '0'; ++dest;
        *dest = '.'; ++dest;
        for (i = 0; i > intDigits; --i) {
            *dest = '0'; ++dest;
        }
    }
    // mantissa
    int firstlen = PR_MIN(intDigits, endp - buf);
    for (i = 0; i < firstlen; i++) {
        *dest = buf[i]; ++dest;
    }
    if (i < endp - buf) {
        if (i > 0) {
            *dest = '.'; ++dest;
        }
        for (; i < endp - buf; i++) {
            *dest = buf[i]; ++dest;
        }
    }
    // trailing zeros
    for (; i < intDigits; i++) {
        *dest = '0'; ++dest;
    }
}