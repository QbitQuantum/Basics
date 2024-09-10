NTSTATUS AndroidUsbDeviceObject::CreateFDODevice(PWDFDEVICE_INIT device_init) {
  ASSERT_IRQL_PASSIVE();

  ASSERT(!IsTaretDeviceCreated());
  if (IsTaretDeviceCreated())
    return STATUS_INTERNAL_ERROR;

  // Initialize our object attributes first
  WDF_OBJECT_ATTRIBUTES device_attr;
  NTSTATUS status = InitObjectAttributes(&device_attr, NULL);
  ASSERT(NT_SUCCESS(status));
  if (!NT_SUCCESS(status))
    return status;

  // Initialize the pnp_power_callbacks structure.  Callback events for PnP
  // and Power are specified here. If we don't supply any callbacks, the
  // KMDF will take appropriate default actions for an FDO device object.
  // EvtDevicePrepareHardware and EvtDeviceReleaseHardware are major entry
  // points for initializing / cleaning up our device. Probably, we can leave
  // the rest to the framework.
  WDF_PNPPOWER_EVENT_CALLBACKS pnp_power_callbacks;
  WDF_PNPPOWER_EVENT_CALLBACKS_INIT(&pnp_power_callbacks);
  pnp_power_callbacks.EvtDevicePrepareHardware =
    EvtDevicePrepareHardwareEntry;
  pnp_power_callbacks.EvtDeviceReleaseHardware =
    EvtDeviceReleaseHardwareEntry;
  WdfDeviceInitSetPnpPowerEventCallbacks(device_init, &pnp_power_callbacks);

  // Initialize the request attributes to specify the context size and type
  // for every request created by framework for this device.
  WDF_OBJECT_ATTRIBUTES request_attr;
  WDF_OBJECT_ATTRIBUTES_INIT(&request_attr);
  WDF_OBJECT_ATTRIBUTES_SET_CONTEXT_TYPE(&request_attr, AndroidUsbWdfRequestContext);
  WdfDeviceInitSetRequestAttributes(device_init, &request_attr);

  // Initialize WDF_FILEOBJECT_CONFIG_INIT struct to tell the KMDF that we are
  // interested in handling Create requests that get genereated when an
  // application or another kernel component opens a handle through the device.
  // We are not interested in receiving cleanup / close IRPs at this point.
  WDF_FILEOBJECT_CONFIG file_config;
  WDF_OBJECT_ATTRIBUTES file_attr;
  WDF_FILEOBJECT_CONFIG_INIT(&file_config,
                             EvtDeviceFileCreateEntry,
                             WDF_NO_EVENT_CALLBACK,
                             WDF_NO_EVENT_CALLBACK);
  WDF_OBJECT_ATTRIBUTES_INIT(&file_attr);
  WDF_OBJECT_ATTRIBUTES_SET_CONTEXT_TYPE(&file_attr,
                                         AndroidUsbWdfObjectContext);
  file_attr.EvtCleanupCallback = AndroidUsbWdfObject::EvtCleanupCallbackEntry;
  file_attr.EvtDestroyCallback = AndroidUsbWdfObject::EvtDestroyCallbackEntry;
  // We will provide our own synchronization for file access
  file_attr.SynchronizationScope = WdfSynchronizationScopeNone;
  WdfDeviceInitSetFileObjectConfig(device_init, &file_config, &file_attr);

  // I/O type is buffered by default. It could be very inefficient if we have
  // large reads / writes through our device.
  WdfDeviceInitSetIoType(device_init, WdfDeviceIoDirect);

  // DeviceInit is completely initialized. So call the framework
  // to create the device and attach it to the lower stack.
  WDFDEVICE wdf_dev = NULL;
  status = WdfDeviceCreate(&device_init, &device_attr, &wdf_dev);
  ASSERT(NT_SUCCESS(status) && (NULL != wdf_dev));
  if (!NT_SUCCESS(status))
    return status;

  // Save handle to the created device
  set_wdf_object(wdf_dev);

  // Tell the framework to set the SurpriseRemovalOK in the DeviceCaps so
  // that we don't get the popup in usermode (on Win2K) when we surprise
  // remove the device.
  WDF_DEVICE_PNP_CAPABILITIES pnp_caps;
  WDF_DEVICE_PNP_CAPABILITIES_INIT(&pnp_caps);
  pnp_caps.SurpriseRemovalOK = WdfTrue;
  WdfDeviceSetPnpCapabilities(wdf_device(), &pnp_caps);

  // Create our default queue object for this device to start receiving I/O
  status = CreateDefaultQueue();
  ASSERT(NT_SUCCESS(status));
  if (!NT_SUCCESS(status))
    return status;

  // Register a device interface so that app can find our device and talk to it.
  status = WdfDeviceCreateDeviceInterface(wdf_device(), &android_guid, NULL);
  ASSERT(NT_SUCCESS(status));
  if (!NT_SUCCESS(status))
    return status;

  // Initialize our extension to that device. We will do this at the very end
  // so we know that we successfully passed entire device create chain when
  // we are called with other callbacks to that device.
  status = InitializeContext();
  ASSERT(NT_SUCCESS(status));
  if (!NT_SUCCESS(status))
    return status;

  return STATUS_SUCCESS;
}