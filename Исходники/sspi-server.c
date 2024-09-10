static
DWORD
SignServer(
    IN INT nSocket,
    IN CredHandle *pServerCreds,
    IN ULONG AscFlags
    )
{
    DWORD dwError = ERROR_SUCCESS;
    ULONG ulQop = 0;
    INT nContextAcquired = 0;
    ULONG nIndex = 0;
    SecBuffer TransmitBuffer;
    SecBuffer MsgBuffer;
    SecBuffer WrapBuffers[2] = {0};
    SecBufferDesc WrapBufferDesc;
    CtxtHandle Context;
    SecPkgContext_Names Names;
    SecPkgContext_Sizes Sizes;
    SecPkgContext_SessionKey SessionKey;

    memset(&TransmitBuffer, 0, sizeof(SecBuffer));
    memset(&MsgBuffer, 0, sizeof(SecBuffer));
    memset(&WrapBufferDesc, 0, sizeof(SecBufferDesc));
    memset(&Context, 0, sizeof(CtxtHandle));
    memset(&Names, 0, sizeof(SecPkgContext_Names));
    memset(&Sizes, 0, sizeof(SecPkgContext_Sizes));
    memset(&SessionKey, 0, sizeof(SecPkgContext_SessionKey));

    /* Establish a context with the client */
    dwError = ServerEstablishContext(
        nSocket,
        pServerCreds,
        &Context,
        AscFlags
        );

    BAIL_ON_ERROR(dwError);

    dwError = QueryContextAttributes(
        &Context,
        SECPKG_ATTR_NAMES,
        &Names
        );

    if (dwError)
    {
        printf("Unable to query context: %d\n", dwError);
    }
    else
    {
        printf("Context is for user: %s\n", Names.sUserName);
    }

    dwError = QueryContextAttributes(
        &Context,
        SECPKG_ATTR_SESSION_KEY,
        &SessionKey
        );

    if (dwError)
    {
        printf("Unable to query context: %X\n", dwError);
    }
    else
    {
        printf("Session Key: ");
        for(nIndex = 0; nIndex < SessionKey.SessionKeyLength; nIndex++)
        {
            printf("%02X ", SessionKey.SessionKey[nIndex]);
        }
        printf("\n\n");
    }

    printf("Server accepted context successfully!\n");

    // for clean up... once we've established a context, we must clean it up on
    // future failures.
    nContextAcquired = 1;

    dwError = QueryContextAttributes
        (
        &Context,
        SECPKG_ATTR_SIZES,
        &Sizes
        );

    BAIL_ON_ERROR(dwError);

    /* Receive the sealed message token */
    dwError = RecvToken(nSocket, &TransmitBuffer);
    BAIL_ON_ERROR(dwError);

    printf("RECEIVED:\n");
    DumpBuffer(TransmitBuffer.pvBuffer, TransmitBuffer.cbBuffer);
    printf("\n");

    WrapBufferDesc.cBuffers = 2;
    WrapBufferDesc.pBuffers = WrapBuffers;
    WrapBufferDesc.ulVersion = SECBUFFER_VERSION;

    WrapBuffers[0].BufferType = SECBUFFER_TOKEN;
    WrapBuffers[0].pvBuffer = TransmitBuffer.pvBuffer;
    WrapBuffers[0].cbBuffer = Sizes.cbMaxSignature;

    WrapBuffers[1].BufferType = SECBUFFER_DATA;
    WrapBuffers[1].cbBuffer = TransmitBuffer.cbBuffer - Sizes.cbMaxSignature;
    WrapBuffers[1].pvBuffer = (PBYTE)TransmitBuffer.pvBuffer + Sizes.cbMaxSignature;

    dwError = DecryptMessage(
        &Context,
        &WrapBufferDesc,
        0,                  // no sequence number
        &ulQop
        );

    if (dwError)
    {
        // When we bail, this var will try to be freed which is a bad thing...
        // the memory will be freed when TransmitBuffer is freed, so it's ok
        // to set this buffer to NULL here.
        WrapBuffers[1].pvBuffer = NULL;
        printf("Unable to decrypt message\n");
    }

    BAIL_ON_ERROR(dwError);

    MsgBuffer = WrapBuffers[1];

    printf("Received message '%.*s' from client\n", MsgBuffer.cbBuffer, MsgBuffer.pvBuffer);

    /* Produce a signature block for the message */

    WrapBuffers[0] = MsgBuffer;

    WrapBuffers[1].BufferType = SECBUFFER_TOKEN;
    WrapBuffers[1].cbBuffer = Sizes.cbMaxSignature;
    WrapBuffers[1].pvBuffer = malloc(Sizes.cbMaxSignature);

    if (WrapBuffers[1].pvBuffer == NULL)
    {
        dwError = ERROR_NOT_ENOUGH_MEMORY;
        BAIL_ON_ERROR(dwError);
    }

    dwError = MakeSignature(
        &Context,
        0,
        &WrapBufferDesc,
        0
        );

    if (dwError)
    {
        printf("Unable to MakeSignature");
    }

    BAIL_ON_ERROR(dwError);

    free(TransmitBuffer.pvBuffer);

    TransmitBuffer = WrapBuffers[1];
    WrapBuffers[1].pvBuffer = NULL;
    WrapBuffers[1].cbBuffer = 0;

    /* Send the signature block to the client */

    dwError = SendToken(nSocket, &TransmitBuffer);
    BAIL_ON_ERROR(dwError);

    free(TransmitBuffer.pvBuffer);
    TransmitBuffer.pvBuffer = NULL;
    TransmitBuffer.cbBuffer = 0;

    /* Delete context */

    dwError = DeleteSecurityContext( &Context );
    BAIL_ON_ERROR(dwError);

finish:
    return dwError;
error:
    if (Names.sUserName)
    {
        FreeContextBuffer(Names.sUserName);
    }
    if (TransmitBuffer.pvBuffer)
    {
        free(TransmitBuffer.pvBuffer);
        TransmitBuffer.pvBuffer = NULL;
        TransmitBuffer.cbBuffer = 0;
    }
    if (WrapBuffers[1].pvBuffer)
    {
        free(WrapBuffers[1].pvBuffer);
        WrapBuffers[1].pvBuffer = NULL;
        WrapBuffers[1].cbBuffer = 0;
    }
    if (nContextAcquired)
    {
        DeleteSecurityContext(&Context);
    }
    goto finish;
}