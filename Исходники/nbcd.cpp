Decimal & Decimal::multiply(const Decimal & other)
{
    int low1, high1, low2, high2, lowt, hight;

    clip(low1, high1);
    other.clip(low2, high2);
    lowt = low1+low2-zeroDigit;
    if (lowt < 0) lowt = 0;
    hight = high1 + high2 - zeroDigit;
    if (hight >= maxDigits) hight = maxDigits-1;
    else if (hight < 0)
    {
        if (hight < -1)
        {
            setZero();
            return *this;
        }
        hight = 0;
    }


    unsigned temp[maxDigits*2];
    _clear(temp);
//  memset(temp+low1+low2, 0, (high1+high2-low1-low2+2)*sizeof(unsigned));  // only need to clear part of the target we're adding to.

    //More: could copy across 1st time round - might be worth it.
    const byte * digits1 = digits;
    const byte * digits2 = other.digits;
    for (int i = low1; i <= high1; i++)
    {
        byte next = digits1[i];
        if (next)
        {
            for (int j=low2; j <= high2; j++)
                temp[i+j] += next * digits2[j];
        }
    }

    //Now copy the results, taking cary of the carries 
    unsigned carry = 0;
    int j;
    for (j = low1+low2 - zeroDigit; j < lowt; j++)
        carry = (temp[j+zeroDigit]+carry)/10;
    for (j = lowt; j <= hight; j++)
    {
        div_t next = div(temp[j+zeroDigit]+carry, 10);
        digits[j] = next.rem;
        carry = next.quot;
    }
    if ((hight < maxDigits-1) && (carry != 0))
        digits[++hight] = carry % 10;

    lsb = lowt;
    msb = hight;
    negative ^= other.negative;
    return *this;
}