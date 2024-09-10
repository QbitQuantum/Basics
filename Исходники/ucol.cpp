U_CAPI UCollationStrength U_EXPORT2
ucol_getStrength(const UCollator *coll)
{
    UErrorCode status = U_ZERO_ERROR;
    return ucol_getAttribute(coll, UCOL_STRENGTH, &status);
}