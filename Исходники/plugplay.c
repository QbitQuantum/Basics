static NTSTATUS
IopGetRelatedDevice(PPLUGPLAY_CONTROL_RELATED_DEVICE_DATA RelatedDeviceData)
{
    UNICODE_STRING RootDeviceName;
    PDEVICE_OBJECT DeviceObject = NULL;
    PDEVICE_NODE DeviceNode = NULL;
    PDEVICE_NODE RelatedDeviceNode;
    UNICODE_STRING TargetDeviceInstance;
    NTSTATUS Status = STATUS_SUCCESS;
    ULONG Relation = 0;
    ULONG MaximumLength = 0;

    DPRINT("IopGetRelatedDevice() called\n");
    DPRINT("Device name: %wZ\n", &RelatedDeviceData->TargetDeviceInstance);

    Status = IopCaptureUnicodeString(&TargetDeviceInstance, &RelatedDeviceData->TargetDeviceInstance);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    _SEH2_TRY
    {
        Relation = RelatedDeviceData->Relation;
        MaximumLength = RelatedDeviceData->RelatedDeviceInstanceLength;
        ProbeForWrite(RelatedDeviceData->RelatedDeviceInstance,
                      MaximumLength,
                      sizeof(WCHAR));
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        if (TargetDeviceInstance.Buffer != NULL)
        {
            ExFreePool(TargetDeviceInstance.Buffer);
        }
        _SEH2_YIELD(return _SEH2_GetExceptionCode());
    }
    _SEH2_END;

    RtlInitUnicodeString(&RootDeviceName,
                         L"HTREE\\ROOT\\0");
    if (RtlEqualUnicodeString(&TargetDeviceInstance,
                              &RootDeviceName,
                              TRUE))
    {
        DeviceNode = IopRootDeviceNode;
        if (TargetDeviceInstance.Buffer != NULL)
        {
            ExFreePool(TargetDeviceInstance.Buffer);
        }
    }
    else
    {
        /* Get the device object */
        DeviceObject = IopGetDeviceObjectFromDeviceInstance(&TargetDeviceInstance);
        if (TargetDeviceInstance.Buffer != NULL)
        {
            ExFreePool(TargetDeviceInstance.Buffer);
        }
        if (DeviceObject == NULL)
            return STATUS_NO_SUCH_DEVICE;

        DeviceNode = ((PEXTENDED_DEVOBJ_EXTENSION)DeviceObject->DeviceObjectExtension)->DeviceNode;
    }

    switch (Relation)
    {
        case PNP_GET_PARENT_DEVICE:
            RelatedDeviceNode = DeviceNode->Parent;
            break;

        case PNP_GET_CHILD_DEVICE:
            RelatedDeviceNode = DeviceNode->Child;
            break;

        case PNP_GET_SIBLING_DEVICE:
            RelatedDeviceNode = DeviceNode->Sibling;
            break;

        default:
            if (DeviceObject != NULL)
            {
                ObDereferenceObject(DeviceObject);
            }

            return STATUS_INVALID_PARAMETER;
    }

    if (RelatedDeviceNode == NULL)
    {
        if (DeviceObject)
        {
            ObDereferenceObject(DeviceObject);
        }

        return STATUS_NO_SUCH_DEVICE;
    }

    if (RelatedDeviceNode->InstancePath.Length > MaximumLength)
    {
        if (DeviceObject)
        {
            ObDereferenceObject(DeviceObject);
        }

        return STATUS_BUFFER_TOO_SMALL;
    }

    /* Copy related device instance name */
    _SEH2_TRY
    {
        RtlCopyMemory(RelatedDeviceData->RelatedDeviceInstance,
                      RelatedDeviceNode->InstancePath.Buffer,
                      RelatedDeviceNode->InstancePath.Length);
        RelatedDeviceData->RelatedDeviceInstanceLength = RelatedDeviceNode->InstancePath.Length;
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        Status = _SEH2_GetExceptionCode();
    }
    _SEH2_END;

    if (DeviceObject != NULL)
    {
        ObDereferenceObject(DeviceObject);
    }

    DPRINT("IopGetRelatedDevice() done\n");

    return Status;
}