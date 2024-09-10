static
DWORD
CallServer(
    IN PCSTR pHost,
    IN USHORT usPort,
    IN PCSTR pSPN,
    IN PCSTR pServiceName,
    IN PCSTR pServicePassword,
    IN PCSTR pServiceRealm,
    IN ULONG DelegFlag,
    IN PCSTR pMsg,
    IN PCSTR pSecPkgName,
    IN INT nSignOnly
    )
{
    DWORD dwError = ERROR_SUCCESS;
    SecBuffer WrapBuffers[3] = {0};
    INT nSocket = INVALID_SOCKET;
    ULONG nIndex = 0;
    ULONG RetFlags = 0;
    ULONG QopState = 0;
    INT nContextAcquired = 0;

    CtxtHandle Context;
    SecBuffer InBuffer;
    SecBuffer OutBuffer;
    SecBufferDesc InBufferDesc;
    SecPkgContext_Sizes Sizes;
    SecPkgContext_Names Names;
#if 0
    SecPkgContext_AccessToken Token;
    SecPkgContext_NativeNames NativeNames;
    HANDLE TokenHandle;
    SecPkgContext_Authority Authority;
    TOKEN_USER User;
    DWORD NeedLength = 0;
#endif
    SecPkgContext_TargetInformation Target;
    SecPkgContext_SessionKey SessionKey;

    memset(&Context, 0, sizeof(CtxtHandle));
    memset(&InBuffer, 0, sizeof(SecBuffer));
    memset(&OutBuffer, 0, sizeof(SecBuffer));
    memset(&InBufferDesc, 0, sizeof(SecBufferDesc));
    memset(&Sizes, 0, sizeof(SecPkgContext_Sizes));

    /* Open connection */

    dwError = ConnectToServer(pHost, usPort, &nSocket);
    BAIL_ON_ERROR(dwError);

    /* Establish context */
    dwError = ClientEstablishContext(
            pSPN,
            nSocket,
            pServiceName,
            pServicePassword,
            pServiceRealm,
            DelegFlag,
            &Context,
            pSecPkgName,
            &RetFlags
            );

    BAIL_ON_ERROR(dwError);

    nContextAcquired = 1;

    dwError = QueryContextAttributes(
        &Context,
        SECPKG_ATTR_NAMES,
        &Names);
    BAIL_ON_ERROR(dwError);

    printf("Context is for user: %s\n", Names.sUserName);

#if 0
    dwError = QueryContextAttributes(
                    &Context,
                    SECPKG_ATTR_ACCESS_TOKEN,
                    &Token);
    BAIL_ON_ERROR(dwError);

    dwError = GetTokenInformation(
                    &Context,
                    TokenUser,
                    &User,
                    sizeof(User),
                    &NeedLength);
    BAIL_ON_ERROR(dwError);

    dwError = QuerySecurityContextToken(
            &Context,
            &TokenHandle);
    BAIL_ON_ERROR(dwError);

    dwError = QueryContextAttributes(
                    &Context,
                    SECPKG_ATTR_AUTHORITY,
                    &Authority);
    BAIL_ON_ERROR(dwError);

    printf("Authority is %s\n", Authority.sAuthorityName);

    dwError = QueryContextAttributes(
                    &Context,
                    SECPKG_ATTR_NATIVE_NAMES,
                    &NativeNames);
    BAIL_ON_ERROR(dwError);
#endif

    dwError = QueryContextAttributes(
                    &Context,
                    SECPKG_ATTR_TARGET_INFORMATION,
                    &Target);
    if (dwError == SEC_E_UNSUPPORTED_FUNCTION)
    {
        printf("Querying server is unsupported\n");
    }
    else
    {
        BAIL_ON_ERROR(dwError);

        printf("Context is for server %s\n", Target.MarshalledTargetInfo);
    }

    dwError = QueryContextAttributes(
        &Context,
        SECPKG_ATTR_SESSION_KEY,
        &SessionKey);

    if(!dwError)
    {
        printf("Session Key: ");
        for(nIndex = 0; nIndex < SessionKey.SessionKeyLength; nIndex++)
        {
            printf("%02X ", SessionKey.SessionKey[nIndex]);
        }
        printf("\n");
    }

    dwError = QueryContextAttributes(
        &Context,
        SECPKG_ATTR_SIZES,
        &Sizes
        );

    BAIL_ON_ERROR(dwError);

    /* Seal the message */
    InBuffer.pvBuffer = (PVOID) pMsg;
    InBuffer.cbBuffer = (ULONG)strlen(pMsg) + 1;

    //
    // Prepare to encrypt the message
    //

    InBufferDesc.cBuffers = 3;
    InBufferDesc.pBuffers = WrapBuffers;
    InBufferDesc.ulVersion = SECBUFFER_VERSION;

    WrapBuffers[0].cbBuffer = Sizes.cbSecurityTrailer;
    WrapBuffers[0].BufferType = SECBUFFER_TOKEN;
    WrapBuffers[0].pvBuffer = malloc(Sizes.cbSecurityTrailer);

    if (WrapBuffers[0].pvBuffer == NULL)
    {
        dwError = ERROR_NOT_ENOUGH_MEMORY;
        BAIL_ON_ERROR(dwError);
    }

    WrapBuffers[1].BufferType = SECBUFFER_DATA;
    WrapBuffers[1].cbBuffer = InBuffer.cbBuffer;
    WrapBuffers[1].pvBuffer = malloc(WrapBuffers[1].cbBuffer);

    if (WrapBuffers[1].pvBuffer == NULL)
    {
        dwError = ERROR_NOT_ENOUGH_MEMORY;
        BAIL_ON_ERROR(dwError);
    }

    memcpy(
        WrapBuffers[1].pvBuffer,
        InBuffer.pvBuffer,
        InBuffer.cbBuffer
        );

    WrapBuffers[2].BufferType = SECBUFFER_PADDING;
    WrapBuffers[2].cbBuffer = Sizes.cbBlockSize;
    WrapBuffers[2].pvBuffer = malloc(WrapBuffers[2].cbBuffer);

    if (WrapBuffers[2].pvBuffer == NULL)
    {
        dwError = ERROR_NOT_ENOUGH_MEMORY;
        BAIL_ON_ERROR(dwError);
    }

    if (nSignOnly)
    {
        printf("Signing only (not encrypting)\n");
    }

    dwError = EncryptMessage(
        &Context,
        nSignOnly ? SECQOP_WRAP_NO_ENCRYPT : 0,
        &InBufferDesc,
        0);

    BAIL_ON_ERROR(dwError);

    //
    // Create the mesage to send to server
    //

    OutBuffer.cbBuffer = WrapBuffers[0].cbBuffer + WrapBuffers[1].cbBuffer + WrapBuffers[2].cbBuffer;
    OutBuffer.pvBuffer = malloc(OutBuffer.cbBuffer);

    if (OutBuffer.pvBuffer == NULL)
    {
        dwError = ERROR_NOT_ENOUGH_MEMORY;
        BAIL_ON_ERROR(dwError);
    }

    memcpy(
        OutBuffer.pvBuffer,
        WrapBuffers[0].pvBuffer,
        WrapBuffers[0].cbBuffer
        );
    memcpy(
        (PUCHAR) OutBuffer.pvBuffer + (int) WrapBuffers[0].cbBuffer,
        WrapBuffers[1].pvBuffer,
        WrapBuffers[1].cbBuffer
        );
    memcpy(
        (PUCHAR) OutBuffer.pvBuffer + WrapBuffers[0].cbBuffer + WrapBuffers[1].cbBuffer,
        WrapBuffers[2].pvBuffer,
        WrapBuffers[2].cbBuffer
        );

    /* Send to server */
    dwError = SendToken(nSocket, &OutBuffer);
    BAIL_ON_ERROR(dwError);
    printf("Encrypted and sent '%s' to server\n", pMsg);

    free(OutBuffer.pvBuffer);
    OutBuffer.pvBuffer = NULL;
    OutBuffer.cbBuffer = 0;
    free(WrapBuffers[0].pvBuffer);
    WrapBuffers[0].pvBuffer = NULL;
    free(WrapBuffers[1].pvBuffer);
    WrapBuffers[1].pvBuffer = NULL;

    /* Read signature block into OutBuffer */
    dwError = RecvToken(nSocket, &OutBuffer);
    BAIL_ON_ERROR(dwError);

    /* Verify signature block */

    InBufferDesc.cBuffers = 2;
    WrapBuffers[0] = InBuffer;
    WrapBuffers[0].BufferType = SECBUFFER_DATA;
    WrapBuffers[1] = OutBuffer;
    WrapBuffers[1].BufferType = SECBUFFER_TOKEN;

    dwError = VerifySignature(&Context, &InBufferDesc, 0, &QopState);
    BAIL_ON_ERROR(dwError);

    free(OutBuffer.pvBuffer);
    OutBuffer.pvBuffer = NULL;

    /* Delete context */
    dwError = DeleteSecurityContext(&Context);
    BAIL_ON_ERROR(dwError);

    closesocket(nSocket);

finish:
    return dwError;
error:
    if (nContextAcquired)
    {
        DeleteSecurityContext(&Context);
    }
    if (INVALID_SOCKET != nSocket)
    {
        closesocket(nSocket);
    }
    if (WrapBuffers[0].pvBuffer)
    {
        free(WrapBuffers[0].pvBuffer);
    }
    if (WrapBuffers[1].pvBuffer)
    {
        free(WrapBuffers[1].pvBuffer);
    }
    if (WrapBuffers[2].pvBuffer)
    {
        free(WrapBuffers[2].pvBuffer);
    }
    if (OutBuffer.pvBuffer)
    {
        free(OutBuffer.pvBuffer);
    }

    goto finish;
}