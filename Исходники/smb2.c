NTSTATUS
RdrSmb2EncodeTreeConnectRequest(
    PSMB_PACKET pPacket,
    PBYTE* ppCursor,
    PULONG pulRemaining,
    PCWSTR pwszPath
    )
{
    NTSTATUS status = STATUS_SUCCESS;
    PRDR_SMB2_TREE_CONNECT_REQUEST_HEADER pHeader = NULL;
    ULONG ulPathLength = LwRtlWC16StringNumChars(pwszPath);
    PBYTE pFilename = NULL;

    if (ulPathLength > 256)
    {
        status = STATUS_INVALID_PARAMETER;
        BAIL_ON_NT_STATUS(status);
    }

    pHeader = (PRDR_SMB2_TREE_CONNECT_REQUEST_HEADER) *ppCursor;
    /* Advance cursor past header to ensure buffer space */
    status = Advance(ppCursor, pulRemaining, sizeof(*pHeader));
    BAIL_ON_NT_STATUS(status);

    pHeader->usLength = SMB_HTOL16(sizeof(*pHeader) | 0x1);
    pHeader->usPathLength = SMB_HTOL16(ulPathLength * sizeof(WCHAR));

    /* Align to WCHAR */
    status = Align((PBYTE) pPacket->pSMB2Header, ppCursor, pulRemaining, sizeof(WCHAR));
    BAIL_ON_NT_STATUS(status);

    pFilename = *ppCursor;

    /* Fill in offset field */
    pHeader->usPathOffset = SMB_HTOL16((USHORT) PACKET_HEADER_OFFSET(pPacket, pFilename));

    /* Fill in data */
    status = Advance(ppCursor, pulRemaining, ulPathLength * sizeof(WCHAR));
    BAIL_ON_NT_STATUS(status);

    SMB_HTOLWSTR(
        pFilename,
        pwszPath,
        ulPathLength);
    BAIL_ON_NT_STATUS(status);

cleanup:

    return status;

 error:

    goto cleanup;
}