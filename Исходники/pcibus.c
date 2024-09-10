PPCI_REGISTRY_INFO_INTERNAL
NTAPI
INIT_FUNCTION
HalpQueryPciRegistryInfo(VOID)
{
#ifndef _MINIHAL_
    WCHAR NameBuffer[8];
    OBJECT_ATTRIBUTES  ObjectAttributes;
    UNICODE_STRING KeyName, ConfigName, IdentName;
    HANDLE KeyHandle, BusKeyHandle, CardListHandle;
    NTSTATUS Status;
    UCHAR KeyBuffer[sizeof(CM_FULL_RESOURCE_DESCRIPTOR) + 100];
    PKEY_VALUE_FULL_INFORMATION ValueInfo = (PVOID)KeyBuffer;
    UCHAR PartialKeyBuffer[sizeof(KEY_VALUE_PARTIAL_INFORMATION) +
                           sizeof(PCI_CARD_DESCRIPTOR)];
    PKEY_VALUE_PARTIAL_INFORMATION PartialValueInfo = (PVOID)PartialKeyBuffer;
    KEY_FULL_INFORMATION KeyInformation;
    ULONG ResultLength;
    PWSTR Tag;
    ULONG i, ElementCount;
    PCM_FULL_RESOURCE_DESCRIPTOR FullDescriptor;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR PartialDescriptor;
    PPCI_REGISTRY_INFO PciRegInfo;
    PPCI_REGISTRY_INFO_INTERNAL PciRegistryInfo;
    PPCI_CARD_DESCRIPTOR CardDescriptor;

    /* Setup the object attributes for the key */
    RtlInitUnicodeString(&KeyName,
                         L"\\Registry\\Machine\\Hardware\\Description\\"
                         L"System\\MultiFunctionAdapter");
    InitializeObjectAttributes(&ObjectAttributes,
                               &KeyName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);

    /* Open the key */
    Status = ZwOpenKey(&KeyHandle, KEY_READ, &ObjectAttributes);
    if (!NT_SUCCESS(Status)) return NULL;

    /* Setup the receiving string */
    KeyName.Buffer = NameBuffer;
    KeyName.MaximumLength = sizeof(NameBuffer);

    /* Setup the configuration and identifier key names */
    RtlInitUnicodeString(&ConfigName, L"Configuration Data");
    RtlInitUnicodeString(&IdentName, L"Identifier");

    /* Keep looping for each ID */
    for (i = 0; TRUE; i++)
    {
        /* Setup the key name */
        RtlIntegerToUnicodeString(i, 10, &KeyName);
        InitializeObjectAttributes(&ObjectAttributes,
                                   &KeyName,
                                   OBJ_CASE_INSENSITIVE,
                                   KeyHandle,
                                   NULL);

        /* Open it */
        Status = ZwOpenKey(&BusKeyHandle, KEY_READ, &ObjectAttributes);
        if (!NT_SUCCESS(Status))
        {
            /* None left, fail */
            ZwClose(KeyHandle);
            return NULL;
        }

        /* Read the registry data */
        Status = ZwQueryValueKey(BusKeyHandle,
                                 &IdentName,
                                 KeyValueFullInformation,
                                 ValueInfo,
                                 sizeof(KeyBuffer),
                                 &ResultLength);
        if (!NT_SUCCESS(Status))
        {
            /* Failed, try the next one */
            ZwClose(BusKeyHandle);
            continue;
        }

        /* Get the PCI Tag and validate it */
        Tag = (PWSTR)((ULONG_PTR)ValueInfo + ValueInfo->DataOffset);
        if ((Tag[0] != L'P') ||
            (Tag[1] != L'C') ||
            (Tag[2] != L'I') ||
            (Tag[3]))
        {
            /* Not a valid PCI entry, skip it */
            ZwClose(BusKeyHandle);
            continue;
        }

        /* Now read our PCI structure */
        Status = ZwQueryValueKey(BusKeyHandle,
                                 &ConfigName,
                                 KeyValueFullInformation,
                                 ValueInfo,
                                 sizeof(KeyBuffer),
                                 &ResultLength);
        ZwClose(BusKeyHandle);
        if (!NT_SUCCESS(Status)) continue;

        /* We read it OK! Get the actual resource descriptors */
        FullDescriptor  = (PCM_FULL_RESOURCE_DESCRIPTOR)
                          ((ULONG_PTR)ValueInfo + ValueInfo->DataOffset);
        PartialDescriptor = (PCM_PARTIAL_RESOURCE_DESCRIPTOR)
                            ((ULONG_PTR)FullDescriptor->
                                        PartialResourceList.PartialDescriptors);

        /* Check if this is our PCI Registry Information */
        if (PartialDescriptor->Type == CmResourceTypeDeviceSpecific)
        {
            /* It is, stop searching */
            break;
        }
    }

    /* Close the key */
    ZwClose(KeyHandle);

    /* Save the PCI information for later */
    PciRegInfo = (PPCI_REGISTRY_INFO)(PartialDescriptor + 1);

    /* Assume no Card List entries */
    ElementCount = 0;

    /* Set up for checking the PCI Card List key */
    RtlInitUnicodeString(&KeyName,
                         L"\\Registry\\Machine\\System\\CurrentControlSet\\"
                         L"Control\\PnP\\PCI\\CardList");
    InitializeObjectAttributes(&ObjectAttributes,
                               &KeyName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);

    /* Attempt to open it */
    Status = ZwOpenKey(&CardListHandle, KEY_READ, &ObjectAttributes);
    if (NT_SUCCESS(Status))
    {
        /* It exists, so let's query it */
        Status = ZwQueryKey(CardListHandle,
                            KeyFullInformation,
                            &KeyInformation,
                            sizeof(KEY_FULL_INFORMATION),
                            &ResultLength);
        if (!NT_SUCCESS(Status))
        {
            /* Failed to query, so no info */
            PciRegistryInfo = NULL;
        }
        else
        {
            /* Allocate the full structure */
            PciRegistryInfo =
                ExAllocatePoolWithTag(NonPagedPool,
                                      sizeof(PCI_REGISTRY_INFO_INTERNAL) +
                                      (KeyInformation.Values *
                                       sizeof(PCI_CARD_DESCRIPTOR)),
                                       TAG_HAL);
            if (PciRegistryInfo)
            {
                /* Get the first card descriptor entry */
                CardDescriptor = (PPCI_CARD_DESCRIPTOR)(PciRegistryInfo + 1);

                /* Loop all the values */
                for (i = 0; i < KeyInformation.Values; i++)
                {
                    /* Attempt to get the value */
                    Status = ZwEnumerateValueKey(CardListHandle,
                                                 i,
                                                 KeyValuePartialInformation,
                                                 PartialValueInfo,
                                                 sizeof(PartialKeyBuffer),
                                                 &ResultLength);
                    if (!NT_SUCCESS(Status))
                    {
                        /* Something went wrong, stop the search */
                        break;
                    }

                    /* Make sure it is correctly sized */
                    if (PartialValueInfo->DataLength == sizeof(PCI_CARD_DESCRIPTOR))
                    {
                        /* Sure is, copy it over */
                        *CardDescriptor = *(PPCI_CARD_DESCRIPTOR)
                                           PartialValueInfo->Data;

                        /* One more Card List entry */
                        ElementCount++;

                        /* Move to the next descriptor */
                        CardDescriptor = (CardDescriptor + 1);
                    }
                }
            }
        }

        /* Close the Card List key */
        ZwClose(CardListHandle);
    }
    else
    {
       /* No key, no Card List */
       PciRegistryInfo = NULL;
    }

    /* Check if we failed to get the full structure */
    if (!PciRegistryInfo)
    {
        /* Just allocate the basic structure then */
        PciRegistryInfo = ExAllocatePoolWithTag(NonPagedPool,
                                                sizeof(PCI_REGISTRY_INFO_INTERNAL),
                                                TAG_HAL);
        if (!PciRegistryInfo) return NULL;
    }

    /* Save the info we got */
    PciRegistryInfo->MajorRevision = PciRegInfo->MajorRevision;
    PciRegistryInfo->MinorRevision = PciRegInfo->MinorRevision;
    PciRegistryInfo->NoBuses = PciRegInfo->NoBuses;
    PciRegistryInfo->HardwareMechanism = PciRegInfo->HardwareMechanism;
    PciRegistryInfo->ElementCount = ElementCount;

    /* Return it */
    return PciRegistryInfo;
#else
    return NULL;
#endif
}