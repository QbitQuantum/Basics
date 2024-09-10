/*--------------------------------------------------------------------------*/
wchar_t *getVariableValueDefinedInScilab(wchar_t *wcVarName)
{
    wchar_t *VARVALUE = NULL;
    char *varname = NULL;
    int iType	= 0;

    if (wcVarName)
    {
        varname = wide_string_to_UTF8(wcVarName);
        if (varname)
        {
            SciErr sciErr = getNamedVarType(pvApiCtx, varname, &iType);
            if (sciErr.iErr)
            {
                return NULL;
            }

            if (iType == sci_strings)
            {

                int VARVALUElen = 0;
                int m = 0, n = 0;

                sciErr = readNamedMatrixOfWideString(pvApiCtx, varname, &m, &n, &VARVALUElen, &VARVALUE);
                if (sciErr.iErr)
                {
                    return NULL;
                }

                if ( (m == 1) && (n == 1) )
                {
                    VARVALUE = (wchar_t*)MALLOC(sizeof(wchar_t) * (VARVALUElen + 1));
                    if (VARVALUE)
                    {
                        BOOL bConvLong = FALSE;
                        wchar_t *LongName = NULL;
                        sciErr = readNamedMatrixOfWideString(pvApiCtx, varname, &m, &n, &VARVALUElen, &VARVALUE);
                        if (sciErr.iErr)
                        {
                            FREE(VARVALUE);
                            VARVALUE = NULL;
                            return 0;
                        }
                        LongName = getlongpathnameW(VARVALUE, &bConvLong);
                        if (LongName)
                        {
                            FREE(VARVALUE);
                            VARVALUE = LongName;
                        }
                    }
                }
            }
        }
        if (varname)
        {
            FREE(varname);
            varname = NULL;
        }
    }
    return VARVALUE;
}