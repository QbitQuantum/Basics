int
LsaNssChangePassword(
        PSTR pszUser,
        PSTR pszOldPass,
        PSTR pszNewPass,
        PSTR* ppszError)
{
    DWORD dwError = LW_ERROR_SUCCESS;
    PLSA_USER_INFO_0 pInfo = NULL;
    const DWORD dwInfoLevel = 0;

    *ppszError = NULL;

    dwError = LsaNssCommonEnsureConnected(&lsaConnection);
    BAIL_ON_LSA_ERROR(dwError);

    dwError = LsaNssFindUserByAixName(
                lsaConnection.hLsaConnection,
                pszUser,
                dwInfoLevel,
                (PVOID*)&pInfo);
    BAIL_ON_LSA_ERROR(dwError);

    dwError = LsaChangePassword(
                lsaConnection.hLsaConnection,
                pInfo->pszName,
                pszNewPass,
                pszOldPass);
    BAIL_ON_LSA_ERROR(dwError);

cleanup:

    if (pInfo != NULL)
    {
        LsaFreeUserInfo(
                dwInfoLevel,
                (PVOID)pInfo);
    }
    if(dwError != LW_ERROR_SUCCESS)
    {
        LsaNssMapErrorCode(dwError, &errno);
        return -1;
    }
    return 0;

error:
    LsaNssCommonCloseConnection(&lsaConnection);

    goto cleanup;
}