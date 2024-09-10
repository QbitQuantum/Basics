PFEA FindEA(PFEALIST pFeal, PSZ pszName, USHORT usMaxName)
{
    PFEA pFea;
    PBYTE pMax;

    if (!pFeal)
        return NULL;

    pFea = pFeal->list;
    pMax = (PBYTE)pFeal + pFeal->cbList;

    while ((PBYTE)pFea + sizeof (FEA) < pMax)
    {
        PBYTE pName, pValue;

        pName  = (PBYTE)(pFea + 1);
        if (pName >= pMax)
            return NULL;
        pValue = pName + (USHORT)pFea->cbName + 1;
        if (pValue + pFea->cbValue > pMax)
            return NULL;
#if 0
        if (f32Parms.fMessageActive & LOG_EAS)
            Message("FindEA: '%s'", pName);
#endif
        if (pFea->cbName == (BYTE)usMaxName && !memicmp(pName, pszName, usMaxName))
            return pFea;

        pFea = (PFEA)((PBYTE)pFea + sizeof (FEA) + (USHORT)pFea->cbName + 1 + pFea->cbValue);
    }
    return NULL;
}