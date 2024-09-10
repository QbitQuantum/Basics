NTSTATUS
CmpInitializeRegistryNode(
    IN PCONFIGURATION_COMPONENT_DATA CurrentEntry,
    IN HANDLE ParentHandle,
    OUT PHANDLE NewHandle,
    IN INTERFACE_TYPE InterfaceType,
    IN ULONG BusNumber,
    IN PUSHORT DeviceIndexTable
    )

/*++

Routine Description:

    This routine creates a node for the current firmware component
    and puts component data to the data part of the node.

Arguments:

    CurrentEntry - Supplies a pointer to a configuration component.

    Handle - Supplies the parent handle of CurrentEntry node.

    NewHandle - Suppiles a pointer to a HANDLE to receive the handle of
        the newly created node.

    InterfaceType - Specify the Interface type of the bus that the
        CurrentEntry component resides. (See BusNumber also)

    BusNumber - Specify the Bus Number of the bus that the CurrentEntry
        component resides on.  If Bus number is -1, it means InterfaceType
        and BusNumber are meaningless for this component.

Returns:

    None.

--*/
{

    NTSTATUS Status;
    OBJECT_ATTRIBUTES ObjectAttributes;
    UNICODE_STRING KeyName;
    UNICODE_STRING ValueName;
    UNICODE_STRING ValueData;
    HANDLE Handle;
    HANDLE OldHandle;
    ANSI_STRING AnsiString;
    UCHAR Buffer[12];
    WCHAR UnicodeBuffer[12];
    CONFIGURATION_COMPONENT *Component;
    ULONG Disposition;
    ULONG ConfigurationDataLength;
    PCM_FULL_RESOURCE_DESCRIPTOR NewArea;

    Component = &CurrentEntry->ComponentEntry;

    //
    // If the component class is SystemClass, we set its Type to be
    // ArcSystem.  The reason is because the detection code sets
    // its type to MaximumType to indicate it is NOT ARC compatible.
    // Here, we are only interested in building a System Node.  So we
    // change its Type to ArcSystem to ease the setup.
    //

    if (Component->Class == SystemClass) {
        Component->Type = ArcSystem;
    }

    //
    // Create a new key to describe the Component.
    //
    // The type of the component will be used as the keyname of the
    // registry node.  The class is the class of the component.
    //

    InitializeObjectAttributes(
        &ObjectAttributes,
        &(CmTypeName[Component->Type]),
        0,
        ParentHandle,
        NULL
        );
    ObjectAttributes.Attributes |= OBJ_CASE_INSENSITIVE;

    Status = NtCreateKey(                   // Paht may already exist
                &Handle,
                KEY_READ | KEY_WRITE,
                &ObjectAttributes,
                TITLE_INDEX_VALUE,
                &(CmClassName[Component->Class]),
                0,
                &Disposition
                );

    if (!NT_SUCCESS(Status)) {
        return(Status);
    }

    //
    // If this component is NOT a SystemClass component, we will
    // create a subkey to identify the component's ordering.
    //

    if (Component->Class != SystemClass) {

        RtlIntegerToChar(
            DeviceIndexTable[Component->Type]++,
            10,
            12,
            Buffer
            );

        RtlInitAnsiString(
            &AnsiString,
            Buffer
            );

        KeyName.Buffer = (PWSTR)UnicodeBuffer;
        KeyName.Length = 0;
        KeyName.MaximumLength = sizeof(UnicodeBuffer);

        RtlAnsiStringToUnicodeString(
            &KeyName,
            &AnsiString,
            FALSE
            );

        OldHandle = Handle;

        InitializeObjectAttributes(
            &ObjectAttributes,
            &KeyName,
            0,
            OldHandle,
            NULL
            );
        ObjectAttributes.Attributes |= OBJ_CASE_INSENSITIVE;

        Status = NtCreateKey(
                    &Handle,
                    KEY_READ | KEY_WRITE,
                    &ObjectAttributes,
                    TITLE_INDEX_VALUE,
                    &(CmClassName[Component->Class]),
                    0,
                    &Disposition
                    );

        NtClose(OldHandle);

        if (!NT_SUCCESS(Status)) {
            return(Status);
        }

        ASSERT(Disposition == REG_CREATED_NEW_KEY);
    }

    //
    // Create a value which describes the following component information:
    //     Flags, Cersion, Key, AffinityMask.
    //

    RtlInitUnicodeString(
        &ValueName,
        L"Component Information"
        );

    Status = NtSetValueKey(
                Handle,
                &ValueName,
                TITLE_INDEX_VALUE,
                REG_BINARY,
                &Component->Flags,
                FIELD_OFFSET(CONFIGURATION_COMPONENT, ConfigurationDataLength) -
                    FIELD_OFFSET(CONFIGURATION_COMPONENT, Flags)
                );

    if (!NT_SUCCESS(Status)) {
        NtClose(Handle);
        return(Status);
    }

    //
    // Create a value which describes the component identifier, if any.
    //

    if (Component->IdentifierLength) {

        RtlInitUnicodeString(
            &ValueName,
            L"Identifier"
            );

        RtlInitAnsiString(
            &AnsiString,
            Component->Identifier
            );

        RtlAnsiStringToUnicodeString(
            &ValueData,
            &AnsiString,
            TRUE
            );

        Status = NtSetValueKey(
                    Handle,
                    &ValueName,
                    TITLE_INDEX_VALUE,
                    REG_SZ,
                    ValueData.Buffer,
                    ValueData.Length + sizeof( UNICODE_NULL )
                    );

        RtlFreeUnicodeString(&ValueData);

        if (!NT_SUCCESS(Status)) {
            NtClose(Handle);
            return(Status);
        }
    }

    //
    // Create a value entry for component configuration data.
    //

    RtlInitUnicodeString(
        &ValueName,
        L"Configuration Data"
        );

    //
    // Create the configuration data based on CM_FULL_RESOURCE_DESCRIPTOR.
    //
    // Note the configuration data in firmware tree may be in the form of
    // CM_PARTIAL_RESOURCE_LIST or nothing.  In both cases, we need to
    // set up the registry configuration data to be in the form of
    // CM_FULL_RESOURCE_DESCRIPTOR.
    //

    if (CurrentEntry->ConfigurationData) {

        //
        // This component has configuration data, we copy the data
        // to our work area, add some more data items and copy the new
        // configuration data to the registry.
        //

        ConfigurationDataLength = Component->ConfigurationDataLength +
                      FIELD_OFFSET(CM_FULL_RESOURCE_DESCRIPTOR,
                      PartialResourceList);

        //
        // Make sure our reserved area is big enough to hold the data.
        //

        if (ConfigurationDataLength > CmpConfigurationAreaSize) {

            //
            // If reserved area is not big enough, we resize our reserved
            // area.  If, unfortunately, the reallocation fails, we simply
            // loss the configuration data of this particular component.
            //

            NewArea = (PCM_FULL_RESOURCE_DESCRIPTOR)ExAllocatePool(
                                            PagedPool,
                                            ConfigurationDataLength
                                            );

            if (NewArea) {
                CmpConfigurationAreaSize = ConfigurationDataLength;
                ExFreePool(CmpConfigurationData);
                CmpConfigurationData = NewArea;
                RtlMoveMemory(
                    (PUCHAR)&CmpConfigurationData->PartialResourceList.Version,
                    CurrentEntry->ConfigurationData,
                    Component->ConfigurationDataLength
                    );
            } else {
                Component->ConfigurationDataLength = 0;
                CurrentEntry->ConfigurationData = NULL;
            }
        } else {
            RtlMoveMemory(
                (PUCHAR)&CmpConfigurationData->PartialResourceList.Version,
                CurrentEntry->ConfigurationData,
                Component->ConfigurationDataLength
                );
        }

    }

    if (CurrentEntry->ConfigurationData == NULL) {

        //
        // This component has NO configuration data (or we can't resize
        // our reserved area to hold the data), we simple add whatever
        // is required to set up a CM_FULL_RESOURCE_LIST.
        //

        CmpConfigurationData->PartialResourceList.Version = 0;
        CmpConfigurationData->PartialResourceList.Revision = 0;
        CmpConfigurationData->PartialResourceList.Count = 0;
        ConfigurationDataLength = FIELD_OFFSET(CM_FULL_RESOURCE_DESCRIPTOR,
                                               PartialResourceList) +
                                  FIELD_OFFSET(CM_PARTIAL_RESOURCE_LIST,
                                               PartialDescriptors);
    }

    //
    // Set up InterfaceType and BusNumber for the component.
    //

    CmpConfigurationData->InterfaceType = InterfaceType;
    CmpConfigurationData->BusNumber = BusNumber;

    //
    // Write the newly constructed configuration data to the hardware registry
    //

    Status = NtSetValueKey(
                Handle,
                &ValueName,
                TITLE_INDEX_VALUE,
                REG_FULL_RESOURCE_DESCRIPTOR,
                CmpConfigurationData,
                ConfigurationDataLength
                );

    if (!NT_SUCCESS(Status)) {
        NtClose(Handle);
        return(Status);
    }

    *NewHandle = Handle;
    return(STATUS_SUCCESS);

}