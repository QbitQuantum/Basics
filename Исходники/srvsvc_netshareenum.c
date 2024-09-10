NET_API_STATUS
SrvSvcNetShareEnum(
    /* [in] */ handle_t IDL_handle,
    /* [in] */ wchar16_t *server_name,
    /* [in, out, ref] */ UINT32 *level,
    /* [in, out, ref] */ srvsvc_NetShareCtr *ctr,
    /* [in] */ UINT32 preferred_maximum_length,
    /* [out] */ UINT32 *total_entries,
    /* [in, out] */ UINT32 *resume_handle
    )
{
    NTSTATUS ntStatus = 0;
    DWORD dwError = 0;
    PBYTE pInBuffer = NULL;
    DWORD dwInLength = 0;
    PBYTE pOutBuffer = NULL;
    DWORD dwOutLength = 4096;
    IO_FILE_HANDLE hFile = NULL;
    IO_STATUS_BLOCK IoStatusBlock = { 0 };
    ACCESS_MASK DesiredAccess = 0;
    LONG64 AllocationSize = 0;
    FILE_ATTRIBUTES FileAttributes = 0;
    FILE_SHARE_FLAGS ShareAccess = 0;
    FILE_CREATE_DISPOSITION CreateDisposition = 0;
    FILE_CREATE_OPTIONS CreateOptions = 0;
    ULONG IoControlCode = SRV_DEVCTL_ENUM_SHARE;
    wchar16_t wszDriverName[] = SRV_DRIVER_NAME_W;
    IO_FILE_NAME filename =
                        {
                              .RootFileHandle = NULL,
                              .FileName = &wszDriverName[0],
                              .IoNameOptions = 0
                        };
    SHARE_INFO_ENUM_PARAMS EnumParamsIn = { 0 };
    PSHARE_INFO_ENUM_PARAMS pEnumParamsOut = NULL;
    srvsvc_NetShareCtr0 *ctr0 = NULL;
    srvsvc_NetShareCtr1 *ctr1 = NULL;
    srvsvc_NetShareCtr2 *ctr2 = NULL;
    srvsvc_NetShareCtr501 *ctr501 = NULL;
    srvsvc_NetShareCtr502 *ctr502 = NULL;
    SHORT i = 0;

    EnumParamsIn.dwInfoLevel = *level;

    dwError = LwNtStatusToWin32Error(
                  LwShareInfoMarshalEnumParameters(
                        &EnumParamsIn,
                        &pInBuffer,
                        &dwInLength));
    BAIL_ON_SRVSVC_ERROR(dwError);

    dwError = LwNtStatusToWin32Error(
                  NtCreateFile(
                        &hFile,
                        NULL,
                        &IoStatusBlock,
                        &filename,
                        NULL,
                        NULL,
                        DesiredAccess,
                        AllocationSize,
                        FileAttributes,
                        ShareAccess,
                        CreateDisposition,
                        CreateOptions,
                        NULL,
                        0,
                        NULL,
                        NULL));
    BAIL_ON_SRVSVC_ERROR(dwError);

    dwError = LwAllocateMemory(dwOutLength, (void**)&pOutBuffer);
    BAIL_ON_SRVSVC_ERROR(dwError);

    ntStatus = NtDeviceIoControlFile(
                    hFile,
                    NULL,
                    &IoStatusBlock,
                    IoControlCode,
                    pInBuffer,
                    dwInLength,
                    pOutBuffer,
                    dwOutLength
                    );

    while (ntStatus == STATUS_BUFFER_TOO_SMALL) {
        /* We need more space in output buffer to make this call */

        LW_SAFE_FREE_MEMORY(pOutBuffer);
        dwOutLength *= 2;

        dwError = LwAllocateMemory(dwOutLength, (void**)&pOutBuffer);
        BAIL_ON_SRVSVC_ERROR(dwError);

        ntStatus = NtDeviceIoControlFile(
                        hFile,
                        NULL,
                        &IoStatusBlock,
                        IoControlCode,
                        pInBuffer,
                        dwInLength,
                        pOutBuffer,
                        dwOutLength
                        );
    }
    dwError = LwNtStatusToWin32Error(ntStatus);
    BAIL_ON_SRVSVC_ERROR(dwError);


    dwError = LwNtStatusToWin32Error(
                  LwShareInfoUnmarshalEnumParameters(
                        pOutBuffer,
                        IoStatusBlock.BytesTransferred,
                        &pEnumParamsOut));
    BAIL_ON_SRVSVC_ERROR(dwError);

    switch (pEnumParamsOut->dwInfoLevel)
    {
    case 0:
        ctr0 = ctr->ctr0;
        ctr0->count = pEnumParamsOut->dwNumEntries;

        dwError = SrvSvcSrvAllocateMemory(
                      sizeof(*ctr0->array) * ctr0->count,
                      (PVOID*)&ctr0->array);
        BAIL_ON_SRVSVC_ERROR(dwError);

        for (i=0; i<ctr0->count ; i++)
        {
            dwError = SrvSvcSrvCopyShareInfo0(
                          &ctr0->array[i],
                          &pEnumParamsOut->info.p0[i]);
            BAIL_ON_SRVSVC_ERROR(dwError);
        }
        break;

    case 1:
        ctr1 = ctr->ctr1;
        ctr1->count = pEnumParamsOut->dwNumEntries;

        dwError = SrvSvcSrvAllocateMemory(
                      sizeof(*ctr1->array) * ctr1->count,
                      (PVOID*)&ctr1->array);
        BAIL_ON_SRVSVC_ERROR(dwError);

        for (i=0; i<ctr1->count ; i++)
        {
            dwError = SrvSvcSrvCopyShareInfo1(
                          &ctr1->array[i],
                          &pEnumParamsOut->info.p1[i]);
            BAIL_ON_SRVSVC_ERROR(dwError);
        }
        break;

    case 2:
        ctr2 = ctr->ctr2;
        ctr2->count = pEnumParamsOut->dwNumEntries;

        dwError = SrvSvcSrvAllocateMemory(
                      sizeof(*ctr2->array) * ctr2->count,
                      (PVOID*)&ctr2->array);
        BAIL_ON_SRVSVC_ERROR(dwError);

        for (i=0; i<ctr2->count ; i++)
        {
            dwError = SrvSvcSrvCopyShareInfo2(
                          &ctr2->array[i],
                          &pEnumParamsOut->info.p2[i]);
            BAIL_ON_SRVSVC_ERROR(dwError);
        }
        break;

    case 501:
        ctr501 = ctr->ctr501;
        ctr501->count = pEnumParamsOut->dwNumEntries;

        dwError = SrvSvcSrvAllocateMemory(
                      sizeof(*ctr501->array) * ctr501->count,
                      (PVOID*)&ctr501->array);
        BAIL_ON_SRVSVC_ERROR(dwError);

        for (i=0; i<ctr501->count ; i++)
        {
            dwError = SrvSvcSrvCopyShareInfo501(
                          &ctr501->array[i],
                          &pEnumParamsOut->info.p501[i]);
            BAIL_ON_SRVSVC_ERROR(dwError);
        }
        break;

    case 502:
        ctr502 = ctr->ctr502;
        ctr502->count = pEnumParamsOut->dwNumEntries;

        dwError = SrvSvcSrvAllocateMemory(
                      sizeof(*ctr502->array) * ctr502->count,
                      (PVOID*)&ctr502->array);
        BAIL_ON_SRVSVC_ERROR(dwError);

        for (i=0; i<ctr502->count ; i++)
        {
            dwError = SrvSvcSrvCopyShareInfo502(
                          &ctr502->array[i],
                          &pEnumParamsOut->info.p502[i]);
            BAIL_ON_SRVSVC_ERROR(dwError);
        }
        break;

    default:

        dwError = LwNtStatusToWin32Error(STATUS_NOT_SUPPORTED);
        BAIL_ON_SRVSVC_ERROR(dwError);

        break;
    }

    *level         = pEnumParamsOut->dwInfoLevel;
    *total_entries = pEnumParamsOut->dwNumEntries;

cleanup:

    if (hFile)
    {
        NtCloseFile(hFile);
    }

    LW_SAFE_FREE_MEMORY(pInBuffer);
    LW_SAFE_FREE_MEMORY(pOutBuffer);
    LW_SAFE_FREE_MEMORY(pEnumParamsOut);

    return dwError;

error:

    *level         = 0;
    *total_entries = 0;

    goto cleanup;
}