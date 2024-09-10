/*
Function:
GetNumericPattern

Determines the pattern from the decimalFormat and returns the matching pattern's
index from patterns[].
Returns index -1 if no pattern is found.
*/
int GetNumericPattern(const UNumberFormat* pNumberFormat, const char* patterns[], int patternsCount, bool isNegative)
{
    const int INVALID_FORMAT = -1;
    const int MAX_DOTNET_NUMERIC_PATTERN_LENGTH = 6; // example: "(C n)" plus terminator

    UErrorCode ignore = U_ZERO_ERROR;
    int32_t icuPatternLength = unum_toPattern(pNumberFormat, false, nullptr, 0, &ignore);

    std::vector<UChar> icuPattern(icuPatternLength + 1, '\0');

    UErrorCode err = U_ZERO_ERROR;

    unum_toPattern(pNumberFormat, false, icuPattern.data(), icuPattern.size(), &err);

    assert(U_SUCCESS(err));

    std::string normalizedPattern = NormalizeNumericPattern(icuPattern.data(), isNegative);

    assert(normalizedPattern.length() > 0);
    assert(normalizedPattern.length() < MAX_DOTNET_NUMERIC_PATTERN_LENGTH);

    if (normalizedPattern.length() == 0 || normalizedPattern.length() >= MAX_DOTNET_NUMERIC_PATTERN_LENGTH)
    {
        return INVALID_FORMAT;
    }

    for (int i = 0; i < patternsCount; i++)
    {
        if (strcmp(normalizedPattern.c_str(), patterns[i]) == 0)
        {
            return i;
        }
    };

    assert(false); // should have found a valid pattern
    return INVALID_FORMAT;
}