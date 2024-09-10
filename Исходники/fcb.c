FSRTL_COMPARISON_RESULT
NTAPI
FatiCompareNames(PSTRING NameA,
                 PSTRING NameB)
{
    ULONG MinimumLen, i;

    /* Calc the minimum length */
    MinimumLen = NameA->Length < NameB->Length ? NameA->Length :
                                                NameB->Length;

    /* Actually compare them */
    i = (ULONG)RtlCompareMemory( NameA->Buffer, NameB->Buffer, MinimumLen );

    if (i < MinimumLen)
    {
        /* Compare prefixes */
        if (NameA->Buffer[i] < NameB->Buffer[i])
            return LessThan;
        else
            return GreaterThan;
    }

    /* Final comparison */
    if (NameA->Length < NameB->Length)
        return LessThan;
    else if (NameA->Length > NameB->Length)
        return GreaterThan;
    else
        return EqualTo;
}