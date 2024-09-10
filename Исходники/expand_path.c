/*
 *  Expand a %{USERID} token
 *
 *  The %{USERID} token expands to the string representation of the
 *  user's SID.  The user account that will be used is the account
 *  corresponding to the current thread's security token.  This means
 *  that:
 *
 *  - If the current thread token has the anonymous impersonation
 *    level, the call will fail.
 *
 *  - If the current thread is impersonating a token at
 *    SecurityIdentification level the call will fail.
 *
 */
static krb5_error_code
expand_userid(krb5_context context, PTYPE param, const char *postfix,
              char **ret)
{
    int rv = EINVAL;
    HANDLE hThread = NULL;
    HANDLE hToken = NULL;
    PTOKEN_OWNER pOwner = NULL;
    DWORD len = 0;
    LPTSTR strSid = NULL;

    hThread = GetCurrentThread();

    if (!OpenThreadToken(hThread, TOKEN_QUERY,
                         FALSE, /* Open the thread token as the
                                   current thread user. */
                         &hToken)) {

        DWORD le = GetLastError();

        if (le == ERROR_NO_TOKEN) {
            HANDLE hProcess = GetCurrentProcess();

            le = 0;
            if (!OpenProcessToken(hProcess, TOKEN_QUERY, &hToken))
                le = GetLastError();
        }

        if (le != 0) {
            k5_setmsg(context, rv, "Can't open thread token (GLE=%d)", le);
            goto cleanup;
        }
    }

    if (!GetTokenInformation(hToken, TokenOwner, NULL, 0, &len)) {
        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
            k5_setmsg(context, rv,
                      "Unexpected error reading token information (GLE=%d)",
                      GetLastError());
            goto cleanup;
        }

        if (len == 0) {
            k5_setmsg(context, rv,
                      "GetTokenInformation() returned truncated buffer");
            goto cleanup;
        }

        pOwner = malloc(len);
        if (pOwner == NULL) {
            rv = ENOMEM;
            goto cleanup;
        }
    } else {
        k5_setmsg(context, rv,
                  "GetTokenInformation() returned truncated buffer");
        goto cleanup;
    }

    if (!GetTokenInformation(hToken, TokenOwner, pOwner, len, &len)) {
        k5_setmsg(context, rv,
                  "GetTokenInformation() failed.  GLE=%d", GetLastError());
        goto cleanup;
    }

    if (!ConvertSidToStringSid(pOwner->Owner, &strSid)) {
        k5_setmsg(context, rv,
                  "Can't convert SID to string.  GLE=%d", GetLastError());
        goto cleanup;
    }

    *ret = strdup(strSid);
    if (*ret == NULL) {
        rv = ENOMEM;
        goto cleanup;
    }

    rv = 0;

cleanup:
    if (hToken != NULL)
        CloseHandle(hToken);

    if (pOwner != NULL)
        free(pOwner);

    if (strSid != NULL)
        LocalFree(strSid);

    return rv;
}