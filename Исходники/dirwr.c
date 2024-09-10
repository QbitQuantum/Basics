/*
 * rename an existing FAT entry
 */
NTSTATUS
vfatRenameEntry(
    IN PDEVICE_EXTENSION DeviceExt,
    IN PVFATFCB pFcb,
    IN PUNICODE_STRING FileName,
    IN BOOLEAN CaseChangeOnly)
{
    OEM_STRING NameA;
    ULONG StartIndex;
    PVOID Context = NULL;
    LARGE_INTEGER Offset;
    PFATX_DIR_ENTRY pDirEntry;
    NTSTATUS Status;

    DPRINT("vfatRenameEntry(%p, %p, %wZ, %d)\n", DeviceExt, pFcb, FileName, CaseChangeOnly);

    if (pFcb->Flags & FCB_IS_FATX_ENTRY)
    {
        VFAT_DIRENTRY_CONTEXT DirContext;

        /* Open associated dir entry */
        StartIndex = pFcb->startIndex;
        Offset.u.HighPart = 0;
        Offset.u.LowPart = (StartIndex * sizeof(FATX_DIR_ENTRY) / PAGE_SIZE) * PAGE_SIZE;
        _SEH2_TRY
        {
            CcPinRead(pFcb->parentFcb->FileObject, &Offset, PAGE_SIZE, PIN_WAIT, &Context, (PVOID*)&pDirEntry);
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
            DPRINT1("CcPinRead(Offset %x:%x, Length %d) failed\n", Offset.u.HighPart, Offset.u.LowPart, PAGE_SIZE);
            _SEH2_YIELD(return _SEH2_GetExceptionCode());
        }
        _SEH2_END;

        pDirEntry = &pDirEntry[StartIndex % (PAGE_SIZE / sizeof(FATX_DIR_ENTRY))];

        /* Set file name */
        NameA.Buffer = (PCHAR)pDirEntry->Filename;
        NameA.Length = 0;
        NameA.MaximumLength = 42;
        RtlUnicodeStringToOemString(&NameA, FileName, FALSE);
        pDirEntry->FilenameLength = (unsigned char)NameA.Length;

        /* Update FCB */
        DirContext.ShortNameU.Length = 0;
        DirContext.ShortNameU.MaximumLength = 0;
        DirContext.ShortNameU.Buffer = NULL;
        DirContext.LongNameU = *FileName;
        DirContext.DirEntry.FatX = *pDirEntry;

        CcSetDirtyPinnedData(Context, NULL);
        CcUnpinData(Context);

        Status = vfatUpdateFCB(DeviceExt, pFcb, &DirContext, pFcb->parentFcb);
        if (NT_SUCCESS(Status))
        {
            CcPurgeCacheSection(&pFcb->parentFcb->SectionObjectPointers, NULL, 0, FALSE);
        }

        return Status;
    }