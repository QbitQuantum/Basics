NTSTATUS DriverEntry (IN PDRIVER_OBJECT DriverObject,
                      IN PUNICODE_STRING RegistryPath)
{
  UNICODE_STRING DeviceName, DeviceLink;
  NTSTATUS NtStatus;
  PDEVICE_OBJECT DeviceObject = NULL;
  PDEVICE_EXTENSION extension;

  WinDbgPrint("WinPMEM - " PMEM_VERSION " - Physical memory acquisition\n");

#if PMEM_WRITE_ENABLED == 1
  WinDbgPrint("WinPMEM write support available!");
#endif

  WinDbgPrint("Copyright (c) 2017, Michael Cohen <*****@*****.**>\n");

  // Initialize import tables:
  if(PmemGetProcAddresses() != STATUS_SUCCESS) {
    WinDbgPrint("Failed to initialize import table. Aborting.\n");
    goto error;
  };

  RtlInitUnicodeString (&DeviceName, L"\\Device\\" PMEM_DEVICE_NAME);

  // We create our secure device.
  // http://msdn.microsoft.com/en-us/library/aa490540.aspx
  NtStatus = IoCreateDeviceSecure(DriverObject,
                                  sizeof(DEVICE_EXTENSION),
                                  &DeviceName,
                                  FILE_DEVICE_UNKNOWN,
                                  FILE_DEVICE_SECURE_OPEN,
                                  FALSE,
                                  &SDDL_DEVOBJ_SYS_ALL_ADM_ALL,
                                  &GUID_DEVCLASS_PMEM_DUMPER,
                                  &DeviceObject);

  if (!NT_SUCCESS(NtStatus)) {
    WinDbgPrint ("IoCreateDevice failed. => %08X\n", NtStatus);
    return NtStatus;
  }

  DriverObject->MajorFunction[IRP_MJ_CREATE] = wddCreate;
  DriverObject->MajorFunction[IRP_MJ_CLOSE] = wddClose;
  DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = wddDispatchDeviceControl;
  DriverObject->MajorFunction[IRP_MJ_READ] = PmemRead;

#if PMEM_WRITE_ENABLED == 1
  {
    // Make sure that the drivers with write support are clearly marked as such.
    static char TAG[] = "Write Supported";
  }

  // Support writing.
  DriverObject->MajorFunction[IRP_MJ_WRITE] = PmemWrite;
#endif
  DriverObject->DriverUnload = IoUnload;

  // Use buffered IO - a bit slower but simpler to implement, and more
  // efficient for small reads.
  SetFlag(DeviceObject->Flags, DO_BUFFERED_IO );
  ClearFlag(DeviceObject->Flags, DO_DIRECT_IO );
  ClearFlag(DeviceObject->Flags, DO_DEVICE_INITIALIZING);

  RtlInitUnicodeString (&DeviceLink, L"\\DosDevices\\" PMEM_DEVICE_NAME);

  NtStatus = IoCreateSymbolicLink (&DeviceLink, &DeviceName);

  if (!NT_SUCCESS(NtStatus)) {
    WinDbgPrint ("IoCreateSymbolicLink failed. => %08X\n", NtStatus);
    IoDeleteDevice (DeviceObject);
  }

  // Populate globals in kernel context.
  CR3.QuadPart = __readcr3();

  // Initialize the device extension with safe defaults.
  extension = DeviceObject->DeviceExtension;
  extension->mode = ACQUISITION_MODE_PHYSICAL_MEMORY;
  extension->MemoryHandle = 0;

#if _WIN64
  // Disable pte mapping for 32 bit systems.
  extension->pte_mmapper = pte_mmap_windows_new();
  extension->pte_mmapper->loglevel = PTE_ERR;
  extension->mode = ACQUISITION_MODE_PTE_MMAP;
#else
  extension->pte_mmapper = NULL;
#endif

  WinDbgPrint("Driver intialization completed.");
  return NtStatus;

 error:
  return STATUS_UNSUCCESSFUL;
}