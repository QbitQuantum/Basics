/*static*/ bool VirtualBoxSDS::i_getClientUserSid(com::Utf8Str *a_pStrSid, com::Utf8Str *a_pStrUsername)
{
    bool fRet = false;
    a_pStrSid->setNull();
    a_pStrUsername->setNull();

    CoInitializeEx(NULL, COINIT_MULTITHREADED); // is this necessary?
    HRESULT hrc = CoImpersonateClient();
    if (SUCCEEDED(hrc))
    {
        HANDLE hToken = INVALID_HANDLE_VALUE;
        if (::OpenThreadToken(GetCurrentThread(), TOKEN_READ, TRUE /*OpenAsSelf*/, &hToken))
        {
            CoRevertToSelf();

            union
            {
                TOKEN_USER  TokenUser;
                uint8_t     abPadding[SECURITY_MAX_SID_SIZE + 256];
                WCHAR       wszUsername[UNLEN + 1];
            } uBuf;
            RT_ZERO(uBuf);
            DWORD cbActual = 0;
            if (::GetTokenInformation(hToken, TokenUser, &uBuf, sizeof(uBuf), &cbActual))
            {
                WCHAR *pwszString;
                if (ConvertSidToStringSidW(uBuf.TokenUser.User.Sid, &pwszString))
                {
                    try
                    {
                        *a_pStrSid = pwszString;
                        a_pStrSid->toUpper(); /* (just to be on the safe side) */
                        fRet = true;
                    }
                    catch (std::bad_alloc &)
                    {
                        LogRel(("i_GetClientUserSID: std::bad_alloc setting rstrSid.\n"));
                    }
                    LocalFree((HLOCAL)pwszString);

                    /*
                     * Get the username too.  We don't care if this step fails.
                     */
                    if (fRet)
                    {
                        WCHAR           wszUsername[UNLEN * 2 + 1];
                        DWORD           cwcUsername = RT_ELEMENTS(wszUsername);
                        WCHAR           wszDomain[UNLEN * 2 + 1];
                        DWORD           cwcDomain = RT_ELEMENTS(wszDomain);
                        SID_NAME_USE    enmNameUse;
                        if (LookupAccountSidW(NULL, uBuf.TokenUser.User.Sid, wszUsername, &cwcUsername,
                                              wszDomain, &cwcDomain, &enmNameUse))
                        {
                            wszUsername[RT_ELEMENTS(wszUsername) - 1] = '\0';
                            wszDomain[RT_ELEMENTS(wszDomain) - 1] = '\0';
                            try
                            {
                                *a_pStrUsername = wszDomain;
                                a_pStrUsername->append('/');
                                a_pStrUsername->append(Utf8Str(wszUsername));
                            }
                            catch (std::bad_alloc &)
                            {
                                LogRel(("i_GetClientUserSID: std::bad_alloc setting rStrUsername.\n"));
                                a_pStrUsername->setNull();
                            }
                        }
                        else
                            LogRel(("i_GetClientUserSID: LookupAccountSidW failed: %u/%x (cwcUsername=%u, cwcDomain=%u)\n",
                                   GetLastError(), cwcUsername, cwcDomain));
                    }
                }
                else
                    LogRel(("i_GetClientUserSID: ConvertSidToStringSidW failed: %u\n", GetLastError()));
            }
            else
                LogRel(("i_GetClientUserSID: GetTokenInformation/TokenUser failed: %u\n", GetLastError()));
            CloseHandle(hToken);
        }
        else
        {
            CoRevertToSelf();
            LogRel(("i_GetClientUserSID: OpenThreadToken failed: %u\n", GetLastError()));
        }
    }
    else
        LogRel(("i_GetClientUserSID: CoImpersonateClient failed: %Rhrc\n", hrc));
    CoUninitialize();
    return fRet;
}