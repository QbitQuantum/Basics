static inline bool containsASCIIUpperChar(const StringImpl& string)
{
    if (string.is8Bit())
        return containsASCIIUpperChar(string.characters8(), string.length());
    return containsASCIIUpperChar(string.characters16(), string.length());
}