VOID PhModuleProviderUpdate(
    __in PVOID Object
    )
{
    PPH_MODULE_PROVIDER moduleProvider = (PPH_MODULE_PROVIDER)Object;
    PPH_LIST modules;
    ULONG i;

    // If we didn't get a handle when we created the provider,
    // abort (unless this is the System process - in that case
    // we don't need a handle).
    if (!moduleProvider->ProcessHandle && moduleProvider->ProcessId != SYSTEM_PROCESS_ID)
        return;

    modules = PhCreateList(20);

    PhEnumGenericModules(
        moduleProvider->ProcessId,
        moduleProvider->ProcessHandle,
        PH_ENUM_GENERIC_MAPPED_FILES | PH_ENUM_GENERIC_MAPPED_IMAGES,
        EnumModulesCallback,
        modules
        );

    // Look for removed modules.
    {
        PPH_LIST modulesToRemove = NULL;
        ULONG enumerationKey = 0;
        PPH_MODULE_ITEM *moduleItem;

        while (PhEnumHashtable(moduleProvider->ModuleHashtable, (PPVOID)&moduleItem, &enumerationKey))
        {
            BOOLEAN found = FALSE;

            // Check if the module still exists.
            for (i = 0; i < modules->Count; i++)
            {
                PPH_MODULE_INFO module = modules->Items[i];

                if ((*moduleItem)->BaseAddress == module->BaseAddress)
                {
                    found = TRUE;
                    break;
                }
            }

            if (!found)
            {
                // Raise the module removed event.
                PhInvokeCallback(&moduleProvider->ModuleRemovedEvent, *moduleItem);

                if (!modulesToRemove)
                    modulesToRemove = PhCreateList(2);

                PhAddItemList(modulesToRemove, *moduleItem);
            }
        }

        if (modulesToRemove)
        {
            PhAcquireFastLockExclusive(&moduleProvider->ModuleHashtableLock);

            for (i = 0; i < modulesToRemove->Count; i++)
            {
                PhpRemoveModuleItem(
                    moduleProvider,
                    (PPH_MODULE_ITEM)modulesToRemove->Items[i]
                    );
            }

            PhReleaseFastLockExclusive(&moduleProvider->ModuleHashtableLock);
            PhDereferenceObject(modulesToRemove);
        }
    }

    // Go through the queued thread query data.
    {
        PSLIST_ENTRY entry;
        PPH_MODULE_QUERY_DATA data;

        entry = RtlInterlockedFlushSList(&moduleProvider->QueryListHead);

        while (entry)
        {
            data = CONTAINING_RECORD(entry, PH_MODULE_QUERY_DATA, ListEntry);
            entry = entry->Next;

            data->ModuleItem->VerifyResult = data->VerifyResult;
            data->ModuleItem->VerifySignerName = data->VerifySignerName;
            data->ModuleItem->JustProcessed = TRUE;

            PhDereferenceObject(data->ModuleItem);
            PhFree(data);
        }
    }

    // Look for new modules.
    for (i = 0; i < modules->Count; i++)
    {
        PPH_MODULE_INFO module = modules->Items[i];
        PPH_MODULE_ITEM moduleItem;

        moduleItem = PhReferenceModuleItem(moduleProvider, module->BaseAddress);

        if (!moduleItem)
        {
            moduleItem = PhCreateModuleItem();

            moduleItem->BaseAddress = module->BaseAddress;
            PhPrintPointer(moduleItem->BaseAddressString, moduleItem->BaseAddress);
            moduleItem->Size = module->Size;
            moduleItem->Flags = module->Flags;
            moduleItem->Type = module->Type;
            moduleItem->Reserved = 0;
            moduleItem->LoadCount = module->LoadCount;

            moduleItem->Name = module->Name;
            PhReferenceObject(moduleItem->Name);
            moduleItem->FileName = module->FileName;
            PhReferenceObject(moduleItem->FileName);

            PhInitializeImageVersionInfo(
                &moduleItem->VersionInfo,
                PhGetString(moduleItem->FileName)
                );

            moduleItem->IsFirst = i == 0;

            if (moduleItem->Type == PH_MODULE_TYPE_MODULE ||
                moduleItem->Type == PH_MODULE_TYPE_WOW64_MODULE ||
                moduleItem->Type == PH_MODULE_TYPE_MAPPED_IMAGE)
            {
                PH_REMOTE_MAPPED_IMAGE remoteMappedImage;

                // Note:
                // On Windows 7 the LDRP_IMAGE_NOT_AT_BASE flag doesn't appear to be used
                // anymore. Instead we'll check ImageBase in the image headers. We read this in
                // from the process' memory because:
                //
                // 1. It (should be) faster than opening the file and mapping it in, and
                // 2. It contains the correct original image base relocated by ASLR, if present.

                if (NT_SUCCESS(PhLoadRemoteMappedImage(moduleProvider->ProcessHandle, moduleItem->BaseAddress, &remoteMappedImage)))
                {
                    moduleItem->ImageTimeDateStamp = remoteMappedImage.NtHeaders->FileHeader.TimeDateStamp;
                    moduleItem->ImageCharacteristics = remoteMappedImage.NtHeaders->FileHeader.Characteristics;

                    if (remoteMappedImage.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC)
                    {
                        if ((ULONG_PTR)((PIMAGE_OPTIONAL_HEADER32)&remoteMappedImage.NtHeaders->OptionalHeader)->ImageBase != (ULONG_PTR)moduleItem->BaseAddress)
                            moduleItem->Flags |= LDRP_IMAGE_NOT_AT_BASE;

                        moduleItem->ImageDllCharacteristics = ((PIMAGE_OPTIONAL_HEADER32)&remoteMappedImage.NtHeaders->OptionalHeader)->DllCharacteristics;
                    }
                    else if (remoteMappedImage.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
                    {
                        if ((ULONG_PTR)((PIMAGE_OPTIONAL_HEADER64)&remoteMappedImage.NtHeaders->OptionalHeader)->ImageBase != (ULONG_PTR)moduleItem->BaseAddress)
                            moduleItem->Flags |= LDRP_IMAGE_NOT_AT_BASE;

                        moduleItem->ImageDllCharacteristics = ((PIMAGE_OPTIONAL_HEADER64)&remoteMappedImage.NtHeaders->OptionalHeader)->DllCharacteristics;
                    }

                    PhUnloadRemoteMappedImage(&remoteMappedImage);
                }
            }

            if (moduleItem->Type == PH_MODULE_TYPE_MODULE || moduleItem->Type == PH_MODULE_TYPE_KERNEL_MODULE ||
                moduleItem->Type == PH_MODULE_TYPE_WOW64_MODULE || moduleItem->Type == PH_MODULE_TYPE_MAPPED_IMAGE)
            {
                // See if the file has already been verified; if not, queue for verification.

                moduleItem->VerifyResult = PhVerifyFileCached(moduleItem->FileName, &moduleItem->VerifySignerName, TRUE);

                if (moduleItem->VerifyResult == VrUnknown)
                    PhpQueueModuleQuery(moduleProvider, moduleItem);
            }

            // Add the module item to the hashtable.
            PhAcquireFastLockExclusive(&moduleProvider->ModuleHashtableLock);
            PhAddEntryHashtable(moduleProvider->ModuleHashtable, &moduleItem);
            PhReleaseFastLockExclusive(&moduleProvider->ModuleHashtableLock);

            // Raise the module added event.
            PhInvokeCallback(&moduleProvider->ModuleAddedEvent, moduleItem);
        }
        else
        {
            BOOLEAN modified = FALSE;

            if (moduleItem->JustProcessed)
                modified = TRUE;

            moduleItem->JustProcessed = FALSE;

            if (modified)
                PhInvokeCallback(&moduleProvider->ModuleModifiedEvent, moduleItem);

            PhDereferenceObject(moduleItem);
        }
    }

    // Free the modules list.

    for (i = 0; i < modules->Count; i++)
    {
        PPH_MODULE_INFO module = modules->Items[i];

        PhDereferenceObject(module->Name);
        PhDereferenceObject(module->FileName);
        PhFree(module);
    }

    PhDereferenceObject(modules);

    PhInvokeCallback(&moduleProvider->UpdatedEvent, NULL);
}