static bool parseHTMLIntegerInternal(const CharacterType* position, const CharacterType* end, int& value)
{
    // Step 3
    int sign = 1;

    // Step 4
    while (position < end) {
        if (!isHTMLSpace<CharacterType>(*position))
            break;
        ++position;
    }

    // Step 5
    if (position == end)
        return false;
    ASSERT(position < end);

    // Step 6
    if (*position == '-') {
        sign = -1;
        ++position;
    } else if (*position == '+')
        ++position;
    if (position == end)
        return false;
    ASSERT(position < end);

    // Step 7
    if (!isASCIIDigit(*position))
        return false;

    // Step 8
    StringBuilder digits;
    while (position < end) {
        if (!isASCIIDigit(*position))
            break;
        digits.append(*position++);
    }

    // Step 9
    bool ok;
    if (digits.is8Bit())
        value = sign * charactersToIntStrict(digits.characters8(), digits.length(), &ok);
    else
        value = sign * charactersToIntStrict(digits.characters16(), digits.length(), &ok);
    return ok;
}