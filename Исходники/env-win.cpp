RTDECL(int) RTEnvSetUtf8(const char *pszVar, const char *pszValue)
{
    AssertReturn(strchr(pszVar, '=') == NULL, VERR_ENV_INVALID_VAR_NAME);

    size_t cwcVar;
    int rc = RTStrCalcUtf16LenEx(pszVar, RTSTR_MAX, &cwcVar);
    if (RT_SUCCESS(rc))
    {
        size_t cwcValue;
        rc = RTStrCalcUtf16LenEx(pszVar, RTSTR_MAX, &cwcValue);
        if (RT_SUCCESS(rc))
        {
            PRTUTF16 pwszTmp = (PRTUTF16)RTMemTmpAlloc((cwcVar + 1 + cwcValue + 1) * sizeof(RTUTF16));
            if (pwszTmp)
            {
                rc = RTStrToUtf16Ex(pszVar, RTSTR_MAX, &pwszTmp, cwcVar + 1, NULL);
                if (RT_SUCCESS(rc))
                {
                    PRTUTF16 pwszTmpValue = &pwszTmp[cwcVar];
                    *pwszTmpValue++ = '=';
                    rc = RTStrToUtf16Ex(pszValue, RTSTR_MAX, &pwszTmpValue, cwcValue + 1, NULL);
                    if (RT_SUCCESS(rc))
                    {
                        if (!_wputenv(pwszTmp))
                            rc = VINF_SUCCESS;
                        else
                            rc = RTErrConvertFromErrno(errno);
                    }
                }
                RTMemTmpFree(pwszTmp);
            }
            else
                rc = VERR_NO_TMP_MEMORY;
        }
    }
    return rc;
}