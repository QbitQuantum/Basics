static inline UChar32 convertToLowerOrUpper(UChar32 c, ConvertType type)
{
    if (type == ConvertLower)
        return toLower(c);
    else
        return toUpper(c);
}