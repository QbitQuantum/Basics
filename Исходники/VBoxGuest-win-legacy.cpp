RT_C_DECLS_END

#ifdef ALLOC_PRAGMA
# pragma alloc_text(INIT, vbgdNt4CreateDevice)
# pragma alloc_text(INIT, vbgdNt4FindPciDevice)
#endif


/**
 * Legacy helper function to create the device object.
 *
 * @returns NT status code.
 *
 * @param   pDrvObj         The driver object.
 * @param   pDevObj         Unused. NULL. Dunno why it's here, makes no sense.
 * @param   pRegPath        The driver registry path.
 */
NTSTATUS vbgdNt4CreateDevice(PDRIVER_OBJECT pDrvObj, PDEVICE_OBJECT pDevObj, PUNICODE_STRING pRegPath)
{
    Log(("VBoxGuest::vbgdNt4CreateDevice: pDrvObj=%p, pDevObj=%p, pRegPath=%p\n", pDrvObj, pDevObj, pRegPath));

    /*
     * Find our virtual PCI device
     */
    ULONG uBusNumber;
    PCI_SLOT_NUMBER SlotNumber;
    NTSTATUS rc = vbgdNt4FindPciDevice(&uBusNumber, &SlotNumber);
    if (NT_ERROR(rc))
    {
        Log(("VBoxGuest::vbgdNt4CreateDevice: Device not found!\n"));
        return rc;
    }

    /*
     * Create device.
     */
    UNICODE_STRING szDevName;
    RtlInitUnicodeString(&szDevName, VBOXGUEST_DEVICE_NAME_NT);
    PDEVICE_OBJECT pDeviceObject = NULL;
    rc = IoCreateDevice(pDrvObj, sizeof(VBOXGUESTDEVEXTWIN), &szDevName, FILE_DEVICE_UNKNOWN, 0, FALSE, &pDeviceObject);
    if (NT_SUCCESS(rc))
    {
        Log(("VBoxGuest::vbgdNt4CreateDevice: Device created\n"));

        UNICODE_STRING DosName;
        RtlInitUnicodeString(&DosName, VBOXGUEST_DEVICE_NAME_DOS);
        rc = IoCreateSymbolicLink(&DosName, &szDevName);
        if (NT_SUCCESS(rc))
        {
            Log(("VBoxGuest::vbgdNt4CreateDevice: Symlink created\n"));

            /*
             * Setup the device extension.
             */
            Log(("VBoxGuest::vbgdNt4CreateDevice: Setting up device extension ...\n"));

            PVBOXGUESTDEVEXTWIN pDevExt = (PVBOXGUESTDEVEXTWIN)pDeviceObject->DeviceExtension;
            RT_ZERO(*pDevExt);

            Log(("VBoxGuest::vbgdNt4CreateDevice: Device extension created\n"));

            /* Store a reference to ourself. */
            pDevExt->pDeviceObject = pDeviceObject;

            /* Store bus and slot number we've queried before. */
            pDevExt->busNumber  = uBusNumber;
            pDevExt->slotNumber = SlotNumber.u.AsULONG;

#ifdef VBOX_WITH_GUEST_BUGCHECK_DETECTION
            rc = hlpRegisterBugCheckCallback(pDevExt);
#endif

            /* Do the actual VBox init ... */
            if (NT_SUCCESS(rc))
            {
                rc = vbgdNtInit(pDrvObj, pDeviceObject, pRegPath);
                if (NT_SUCCESS(rc))
                {
                    Log(("VBoxGuest::vbgdNt4CreateDevice: Returning rc = 0x%x (succcess)\n", rc));
                    return rc;
                }

                /* bail out */
            }
            IoDeleteSymbolicLink(&DosName);
        }
        else
            Log(("VBoxGuest::vbgdNt4CreateDevice: IoCreateSymbolicLink failed with rc = %#x\n", rc));
        IoDeleteDevice(pDeviceObject);
    }
    else
        Log(("VBoxGuest::vbgdNt4CreateDevice: IoCreateDevice failed with rc = %#x\n", rc));
    Log(("VBoxGuest::vbgdNt4CreateDevice: Returning rc = 0x%x\n", rc));
    return rc;
}