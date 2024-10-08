BOOLEAN
INIT_FUNCTION
NTAPI
ObInitSystem(VOID)
{
    OBJECT_ATTRIBUTES ObjectAttributes;
    UNICODE_STRING Name;
    OBJECT_TYPE_INITIALIZER ObjectTypeInitializer;
    OBP_LOOKUP_CONTEXT Context;
    HANDLE Handle;
    PKPRCB Prcb = KeGetCurrentPrcb();
    PLIST_ENTRY ListHead, NextEntry;
    POBJECT_HEADER Header;
    POBJECT_HEADER_CREATOR_INFO CreatorInfo;
    POBJECT_HEADER_NAME_INFO NameInfo;
    NTSTATUS Status;

    /* Check if this is actually Phase 1 initialization */
    if (ObpInitializationPhase != 0) goto ObPostPhase0;

    /* Initialize the OBJECT_CREATE_INFORMATION List */
    ExInitializeSystemLookasideList(&ObpCreateInfoLookasideList,
                                    NonPagedPool,
                                    sizeof(OBJECT_CREATE_INFORMATION),
                                    'ICbO',
                                    32,
                                    &ExSystemLookasideListHead);

    /* Set the captured UNICODE_STRING Object Name List */
    ExInitializeSystemLookasideList(&ObpNameBufferLookasideList,
                                    PagedPool,
                                    248,
                                    'MNbO',
                                    16,
                                    &ExSystemLookasideListHead);

    /* Temporarily setup both pointers to the shared list */
    Prcb->PPLookasideList[LookasideCreateInfoList].L = &ObpCreateInfoLookasideList;
    Prcb->PPLookasideList[LookasideCreateInfoList].P = &ObpCreateInfoLookasideList;
    Prcb->PPLookasideList[LookasideNameBufferList].L = &ObpNameBufferLookasideList;
    Prcb->PPLookasideList[LookasideNameBufferList].P = &ObpNameBufferLookasideList;

    /* Initialize the security descriptor cache */
    ObpInitSdCache();

    /* Initialize the Default Event */
    KeInitializeEvent(&ObpDefaultObject, NotificationEvent, TRUE);

    /* Initialize the Dos Device Map mutex */
    KeInitializeGuardedMutex(&ObpDeviceMapLock);

    /* Setup default access for the system process */
    PsGetCurrentProcess()->GrantedAccess = PROCESS_ALL_ACCESS;
    PsGetCurrentThread()->GrantedAccess = THREAD_ALL_ACCESS;

    /* Setup the Object Reaper */
    ExInitializeWorkItem(&ObpReaperWorkItem, ObpReapObject, NULL);

    /* Initialize default Quota block */
    PsInitializeQuotaSystem();

    /* Create kernel handle table */
    PsGetCurrentProcess()->ObjectTable = ExCreateHandleTable(NULL);
    ObpKernelHandleTable = PsGetCurrentProcess()->ObjectTable;

    /* Create the Type Type */
    RtlZeroMemory(&ObjectTypeInitializer, sizeof(ObjectTypeInitializer));
    RtlInitUnicodeString(&Name, L"Type");
    ObjectTypeInitializer.Length = sizeof(ObjectTypeInitializer);
    ObjectTypeInitializer.ValidAccessMask = OBJECT_TYPE_ALL_ACCESS;
    ObjectTypeInitializer.UseDefaultObject = TRUE;
    ObjectTypeInitializer.MaintainTypeList = TRUE;
    ObjectTypeInitializer.PoolType = NonPagedPool;
    ObjectTypeInitializer.GenericMapping = ObpTypeMapping;
    ObjectTypeInitializer.DefaultNonPagedPoolCharge = sizeof(OBJECT_TYPE);
    ObjectTypeInitializer.InvalidAttributes = OBJ_OPENLINK;
    ObjectTypeInitializer.DeleteProcedure = ObpDeleteObjectType;
    ObCreateObjectType(&Name, &ObjectTypeInitializer, NULL, &ObpTypeObjectType);

    /* Create the Directory Type */
    RtlInitUnicodeString(&Name, L"Directory");
    ObjectTypeInitializer.ValidAccessMask = DIRECTORY_ALL_ACCESS;
    ObjectTypeInitializer.CaseInsensitive = TRUE;
    ObjectTypeInitializer.MaintainTypeList = FALSE;
    ObjectTypeInitializer.GenericMapping = ObpDirectoryMapping;
    ObjectTypeInitializer.DeleteProcedure = NULL;
    ObjectTypeInitializer.DefaultNonPagedPoolCharge = sizeof(OBJECT_DIRECTORY);
    ObCreateObjectType(&Name, &ObjectTypeInitializer, NULL, &ObDirectoryType);

    /* Create 'symbolic link' object type */
    RtlInitUnicodeString(&Name, L"SymbolicLink");
    ObjectTypeInitializer.DefaultNonPagedPoolCharge = sizeof(OBJECT_SYMBOLIC_LINK);
    ObjectTypeInitializer.GenericMapping = ObpSymbolicLinkMapping;
    ObjectTypeInitializer.ValidAccessMask = SYMBOLIC_LINK_ALL_ACCESS;
    ObjectTypeInitializer.ParseProcedure = ObpParseSymbolicLink;
    ObjectTypeInitializer.DeleteProcedure = ObpDeleteSymbolicLink;
    ObCreateObjectType(&Name, &ObjectTypeInitializer, NULL, &ObSymbolicLinkType);

    /* Phase 0 initialization complete */
    ObpInitializationPhase++;
    return TRUE;

ObPostPhase0:

    /* Re-initialize lookaside lists */
    ObInit2();

    /* Initialize Object Types directory attributes */
    RtlInitUnicodeString(&Name, L"\\");
    InitializeObjectAttributes(&ObjectAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE | OBJ_PERMANENT,
                               NULL,
                               SePublicDefaultUnrestrictedSd);

    /* Create the directory */
    Status = NtCreateDirectoryObject(&Handle,
                                     DIRECTORY_ALL_ACCESS,
                                     &ObjectAttributes);
    if (!NT_SUCCESS(Status)) return FALSE;

    /* Get a handle to it */
    Status = ObReferenceObjectByHandle(Handle,
                                       0,
                                       ObDirectoryType,
                                       KernelMode,
                                       (PVOID*)&ObpRootDirectoryObject,
                                       NULL);
    if (!NT_SUCCESS(Status)) return FALSE;

    /* Close the extra handle */
    Status = NtClose(Handle);
    if (!NT_SUCCESS(Status)) return FALSE;

    /* Initialize Object Types directory attributes */
    RtlInitUnicodeString(&Name, L"\\KernelObjects");
    InitializeObjectAttributes(&ObjectAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE | OBJ_PERMANENT,
                               NULL,
                               NULL);
    
    /* Create the directory */
    Status = NtCreateDirectoryObject(&Handle,
                                     DIRECTORY_ALL_ACCESS,
                                     &ObjectAttributes);
    if (!NT_SUCCESS(Status)) return FALSE;
    
    /* Close the extra handle */
    Status = NtClose(Handle);
    if (!NT_SUCCESS(Status)) return FALSE;

    /* Initialize Object Types directory attributes */
    RtlInitUnicodeString(&Name, L"\\ObjectTypes");
    InitializeObjectAttributes(&ObjectAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE | OBJ_PERMANENT,
                               NULL,
                               NULL);

    /* Create the directory */
    Status = NtCreateDirectoryObject(&Handle,
                                     DIRECTORY_ALL_ACCESS,
                                     &ObjectAttributes);
    if (!NT_SUCCESS(Status)) return FALSE;

    /* Get a handle to it */
    Status = ObReferenceObjectByHandle(Handle,
                                       0,
                                       ObDirectoryType,
                                       KernelMode,
                                       (PVOID*)&ObpTypeDirectoryObject,
                                       NULL);
    if (!NT_SUCCESS(Status)) return FALSE;

    /* Close the extra handle */
    Status = NtClose(Handle);
    if (!NT_SUCCESS(Status)) return FALSE;

    /* Initialize lookup context */
    ObpInitializeLookupContext(&Context);

    /* Lock it */
    ObpAcquireDirectoryLockExclusive(ObpTypeDirectoryObject, &Context);

    /* Loop the object types */
    ListHead = &ObpTypeObjectType->TypeList;
    NextEntry = ListHead->Flink;
    while (ListHead != NextEntry)
    {
        /* Get the creator info from the list */
        CreatorInfo = CONTAINING_RECORD(NextEntry,
                                        OBJECT_HEADER_CREATOR_INFO,
                                        TypeList);

        /* Recover the header and the name header from the creator info */
        Header = (POBJECT_HEADER)(CreatorInfo + 1);
        NameInfo = OBJECT_HEADER_TO_NAME_INFO(Header);

        /* Make sure we have a name, and aren't inserted yet */
        if ((NameInfo) && !(NameInfo->Directory))
        {
            /* Do the initial lookup to setup the context */
            if (!ObpLookupEntryDirectory(ObpTypeDirectoryObject,
                                         &NameInfo->Name,
                                         OBJ_CASE_INSENSITIVE,
                                         FALSE,
                                         &Context))
            {
                /* Insert this object type */
                ObpInsertEntryDirectory(ObpTypeDirectoryObject,
                                        &Context,
                                        Header);
            }
        }

        /* Move to the next entry */
        NextEntry = NextEntry->Flink;
    }

    /* Cleanup after lookup */
    ObpReleaseLookupContext(&Context);

    /* Initialize DOS Devices Directory and related Symbolic Links */
    Status = ObpCreateDosDevicesDirectory();
    if (!NT_SUCCESS(Status)) return FALSE;
    return TRUE;
}