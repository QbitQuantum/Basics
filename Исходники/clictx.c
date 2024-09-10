/*
 * @unimplemented
 */
AUTHZAPI
BOOL
WINAPI
AuthzGetInformationFromContext(IN AUTHZ_CLIENT_CONTEXT_HANDLE hAuthzClientContext,
                               IN AUTHZ_CONTEXT_INFORMATION_CLASS InfoClass,
                               IN DWORD BufferSize,
                               OUT PDWORD pSizeRequired,
                               OUT PVOID Buffer)
{
    BOOL Ret = FALSE;

    if (hAuthzClientContext != NULL && pSizeRequired != NULL)
    {
        PAUTHZ_CLIENT_CONTEXT ClientCtx = (PAUTHZ_CLIENT_CONTEXT)hAuthzClientContext;

        VALIDATE_CLIENTCTX_HANDLE(hAuthzClientContext);

        switch (InfoClass)
        {
            case AuthzContextInfoUserSid:
            {
                DWORD SidLen = GetLengthSid(ClientCtx->UserSid);
                *pSizeRequired = SidLen;
                if (BufferSize < SidLen)
                {
                    SetLastError(ERROR_INSUFFICIENT_BUFFER);
                }
                else
                {
                    Ret = CopySid(SidLen,
                                  (PSID)Buffer,
                                  ClientCtx->UserSid);
                }
                break;
            }

            case AuthzContextInfoGroupsSids:
                SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
                break;

            case AuthzContextInfoRestrictedSids:
                SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
                break;

            case AuthzContextInfoPrivileges:
                SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
                break;

            case AuthzContextInfoExpirationTime:
                *pSizeRequired = sizeof(LARGE_INTEGER);
                if (BufferSize < sizeof(LARGE_INTEGER) || Buffer == NULL)
                {
                    SetLastError(ERROR_INSUFFICIENT_BUFFER);
                }
                else
                {
                    *((PLARGE_INTEGER)Buffer) = ClientCtx->ExpirationTime;
                    Ret = TRUE;
                }
                break;

            case AuthzContextInfoServerContext:
                *pSizeRequired = sizeof(AUTHZ_CLIENT_CONTEXT_HANDLE);
                if (BufferSize < sizeof(AUTHZ_CLIENT_CONTEXT_HANDLE) || Buffer == NULL)
                {
                    SetLastError(ERROR_INSUFFICIENT_BUFFER);
                }
                else
                {
                    *((PAUTHZ_CLIENT_CONTEXT_HANDLE)Buffer) = ClientCtx->ServerContext;
                    Ret = TRUE;
                }
                break;

            case AuthzContextInfoIdentifier:
                *pSizeRequired = sizeof(LUID);
                if (BufferSize < sizeof(LUID) || Buffer == NULL)
                {
                    SetLastError(ERROR_INSUFFICIENT_BUFFER);
                }
                else
                {
                    *((PLUID)Buffer) = ClientCtx->Luid;
                    Ret = TRUE;
                }
                break;

            default:
                SetLastError(ERROR_INVALID_PARAMETER);
                break;
        }
    }
    else
        SetLastError(ERROR_INVALID_PARAMETER);

    return Ret;
}