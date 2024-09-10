void UL::setValueFromURN(const wchar_t* str, UInt32 strLen)
{
    // Check if the length is correct
    if (strLen != 45)
    {
        return;
    }

    // Check if the prefix is correct
    if (wcsncmp(str, L"urn:x-ul:", 9) != 0)
    {
        return;
    }

    // OK, lets crunch those hex digits
    str += 9;
    UInt32 pos = 0;
    UInt32 byte = 1;
    UInt8 sixteens;
    UInt8 units;
    while ((pos < strLen - 1) && (byte <= 16))
    {
        sixteens = 16 * hexCharToVal(str[pos]);
        units = hexCharToVal(str[pos + 1]);
        setByte(byte, sixteens + units);
        if (pos == 6 || pos == 11 || pos == 16 || pos == 25)
        {
            pos += 3;
        }
        else
        {
            pos += 2;
        }
        ++byte;
    }
}