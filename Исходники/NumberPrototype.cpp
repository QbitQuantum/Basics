static char* toStringWithRadix(RadixBuffer& buffer, double number, unsigned radix)
{
    ASSERT(std::isfinite(number));
    ASSERT(radix >= 2 && radix <= 36);

    // Position the decimal point at the center of the string, set
    // the startOfResultString pointer to point at the decimal point.
    char* decimalPoint = buffer + sizeof(buffer) / 2;
    char* startOfResultString = decimalPoint;

    // Extract the sign.
    bool isNegative = number < 0;
    if (std::signbit(number))
        number = -number;
    double integerPart = floor(number);

    // We use this to test for odd values in odd radix bases.
    // Where the base is even, (e.g. 10), to determine whether a value is even we need only
    // consider the least significant digit. For example, 124 in base 10 is even, because '4'
    // is even. if the radix is odd, then the radix raised to an integer power is also odd.
    // E.g. in base 5, 124 represents (1 * 125 + 2 * 25 + 4 * 5). Since each digit in the value
    // is multiplied by an odd number, the result is even if the sum of all digits is even.
    //
    // For the integer portion of the result, we only need test whether the integer value is
    // even or odd. For each digit of the fraction added, we should invert our idea of whether
    // the number is odd if the new digit is odd.
    //
    // Also initialize digit to this value; for even radix values we only need track whether
    // the last individual digit was odd.
    bool integerPartIsOdd = integerPart <= static_cast<double>(0x1FFFFFFFFFFFFFull) && static_cast<int64_t>(integerPart) & 1;
    ASSERT(integerPartIsOdd == static_cast<bool>(fmod(integerPart, 2)));
    bool isOddInOddRadix = integerPartIsOdd;
    uint32_t digit = integerPartIsOdd;

    // Check if the value has a fractional part to convert.
    double fractionPart = number - integerPart;
    if (fractionPart) {
        // Write the decimal point now.
        *decimalPoint = '.';

        // Higher precision representation of the fractional part.
        Uint16WithFraction fraction(fractionPart);

        bool needsRoundingUp = false;
        char* endOfResultString = decimalPoint + 1;

        // Calculate the delta from the current number to the next & previous possible IEEE numbers.
        double nextNumber = nextafter(number, std::numeric_limits<double>::infinity());
        double lastNumber = nextafter(number, -std::numeric_limits<double>::infinity());
        ASSERT(std::isfinite(nextNumber) && !std::signbit(nextNumber));
        ASSERT(std::isfinite(lastNumber) && !std::signbit(lastNumber));
        double deltaNextDouble = nextNumber - number;
        double deltaLastDouble = number - lastNumber;
        ASSERT(std::isfinite(deltaNextDouble) && !std::signbit(deltaNextDouble));
        ASSERT(std::isfinite(deltaLastDouble) && !std::signbit(deltaLastDouble));

        // We track the delta from the current value to the next, to track how many digits of the
        // fraction we need to write. For example, if the value we are converting is precisely
        // 1.2345, so far we have written the digits "1.23" to a string leaving a remainder of
        // 0.45, and we want to determine whether we can round off, or whether we need to keep
        // appending digits ('4'). We can stop adding digits provided that then next possible
        // lower IEEE value is further from 1.23 than the remainder we'd be rounding off (0.45),
        // which is to say, less than 1.2255. Put another way, the delta between the prior
        // possible value and this number must be more than 2x the remainder we'd be rounding off
        // (or more simply half the delta between numbers must be greater than the remainder).
        //
        // Similarly we need track the delta to the next possible value, to dertermine whether
        // to round up. In almost all cases (other than at exponent boundaries) the deltas to
        // prior and subsequent values are identical, so we don't need track then separately.
        if (deltaNextDouble != deltaLastDouble) {
            // Since the deltas are different track them separately. Pre-multiply by 0.5.
            Uint16WithFraction halfDeltaNext(deltaNextDouble, 1);
            Uint16WithFraction halfDeltaLast(deltaLastDouble, 1);

            while (true) {
                // examine the remainder to determine whether we should be considering rounding
                // up or down. If remainder is precisely 0.5 rounding is to even.
                int dComparePoint5 = fraction.comparePoint5();
                if (dComparePoint5 > 0 || (!dComparePoint5 && (radix & 1 ? isOddInOddRadix : digit & 1))) {
                    // Check for rounding up; are we closer to the value we'd round off to than
                    // the next IEEE value would be?
                    if (fraction.sumGreaterThanOne(halfDeltaNext)) {
                        needsRoundingUp = true;
                        break;
                    }
                } else {
                    // Check for rounding down; are we closer to the value we'd round off to than
                    // the prior IEEE value would be?
                    if (fraction < halfDeltaLast)
                        break;
                }

                ASSERT(endOfResultString < (buffer + sizeof(buffer) - 1));
                // Write a digit to the string.
                fraction *= radix;
                digit = fraction.floorAndSubtract();
                *endOfResultString++ = radixDigits[digit];
                // Keep track whether the portion written is currently even, if the radix is odd.
                if (digit & 1)
                    isOddInOddRadix = !isOddInOddRadix;

                // Shift the fractions by radix.
                halfDeltaNext *= radix;
                halfDeltaLast *= radix;
            }
        } else {
            // This code is identical to that above, except since deltaNextDouble != deltaLastDouble
            // we don't need to track these two values separately.
            Uint16WithFraction halfDelta(deltaNextDouble, 1);

            while (true) {
                int dComparePoint5 = fraction.comparePoint5();
                if (dComparePoint5 > 0 || (!dComparePoint5 && (radix & 1 ? isOddInOddRadix : digit & 1))) {
                    if (fraction.sumGreaterThanOne(halfDelta)) {
                        needsRoundingUp = true;
                        break;
                    }
                } else if (fraction < halfDelta)
                    break;

                ASSERT(endOfResultString < (buffer + sizeof(buffer) - 1));
                fraction *= radix;
                digit = fraction.floorAndSubtract();
                if (digit & 1)
                    isOddInOddRadix = !isOddInOddRadix;
                *endOfResultString++ = radixDigits[digit];

                halfDelta *= radix;
            }
        }

        // Check if the fraction needs rounding off (flag set in the loop writing digits, above).
        if (needsRoundingUp) {
            // Whilst the last digit is the maximum in the current radix, remove it.
            // e.g. rounding up the last digit in "12.3999" is the same as rounding up the
            // last digit in "12.3" - both round up to "12.4".
            while (endOfResultString[-1] == radixDigits[radix - 1])
                --endOfResultString;

            // Radix digits are sequential in ascii/unicode, except for '9' and 'a'.
            // E.g. the first 'if' case handles rounding 67.89 to 67.8a in base 16.
            // The 'else if' case handles rounding of all other digits.
            if (endOfResultString[-1] == '9')
                endOfResultString[-1] = 'a';
            else if (endOfResultString[-1] != '.')
                ++endOfResultString[-1];
            else {
                // One other possibility - there may be no digits to round up in the fraction
                // (or all may be been rounded off already), in which case we may need to
                // round into the integer portion of the number. Remove the decimal point.
                --endOfResultString;
                // In order to get here there must have been a non-zero fraction, in which case
                // there must be at least one bit of the value's mantissa not in use in the
                // integer part of the number. As such, adding to the integer part should not
                // be able to lose precision.
                ASSERT((integerPart + 1) - integerPart == 1);
                ++integerPart;
            }
        } else {
            // We only need to check for trailing zeros if the value does not get rounded up.
            while (endOfResultString[-1] == '0')
                --endOfResultString;
        }

        *endOfResultString = '\0';
        ASSERT(endOfResultString < buffer + sizeof(buffer));
    } else
        *decimalPoint = '\0';

    BigInteger units(integerPart);

    // Always loop at least once, to emit at least '0'.
    do {
        ASSERT(buffer < startOfResultString);

        // Read a single digit and write it to the front of the string.
        // Divide by radix to remove one digit from the value.
        digit = units.divide(radix);
        *--startOfResultString = radixDigits[digit];
    } while (!!units);

    // If the number is negative, prepend '-'.
    if (isNegative)
        *--startOfResultString = '-';
    ASSERT(buffer <= startOfResultString);

    return startOfResultString;
}