NTSTATUS PPJoyBus_AddDevice (IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT PhysicalDeviceObject)
{
 NTSTATUS			ntStatus;
 PDEVICE_OBJECT		DeviceObject;
 PBUS_DEVICE_DATA	BusDeviceData;

 PAGED_CODE ();

 ntStatus= STATUS_SUCCESS;

 PPJOY_DBGPRINT (FILE_PPJOYBUS|PPJOY_FENTRY, ("PPJoyBus_AddDevice(DriverObject=0x%p,FunctionalDeviceObject=0x%p)",DriverObject,PhysicalDeviceObject) );

 /* Create our FDO device */
 ntStatus= IoCreateDevice (DriverObject,sizeof(BUS_DEVICE_DATA),NULL,FILE_DEVICE_BUS_EXTENDER,FILE_DEVICE_SECURE_OPEN,TRUE,&DeviceObject);
 /* Check to see if we could create the device. If not, exit. */
 if (!NT_SUCCESS (ntStatus)) 
 {
  PPJoyBus_WriteEventLog (PPJ_MSG_ERRORCREATINGBUS,&ntStatus,sizeof(ntStatus),L"");
  PPJOY_DBGPRINT (FILE_PPJOYBUS|PPJOY_ERROR, ("PPJoyBus_AddDevice: IoCreateDevice failed status= 0x%x)",ntStatus) );
  goto ExitNoDelete;
 }

 /* Setup our DeviceExtension */
 BusDeviceData= (PBUS_DEVICE_DATA) DeviceObject->DeviceExtension;
 RtlZeroMemory (BusDeviceData,sizeof(BUS_DEVICE_DATA));
 BusDeviceData->Flags|= PPJFLAGS_ISBUSDEV;

 /* Tell IOManager et al that we are pagable. */
 DeviceObject->Flags|= DO_POWER_PAGABLE;

 /* Attempt to register an interface for this DeviceObject. It will be */
 /* called by the configuration utility to add and remove joysticks.   */
 ntStatus= IoRegisterDeviceInterface (PhysicalDeviceObject,(LPGUID) &GUID_PPJOY_BUS,NULL,&BusDeviceData->InterfaceName);
 /* If we could not register the interface then we exit and delete the DO */
 if (!NT_SUCCESS (ntStatus))
 {
  PPJOY_DBGPRINT (FILE_PPJOYBUS|PPJOY_ERROR, ("PPJoyBus_AddDevice: IoRegisterDeviceInterface failed status= 0x%x)",ntStatus) );
  PPJoyBus_WriteEventLog (PPJ_MSG_ERRORBUSIF,&ntStatus,sizeof(ntStatus),L"");
  goto ExitDeleteDevice;
 }

 PPJOY_DBGPRINT (FILE_PPJOYBUS|PPJOY_BABBLE2, ("PPJoyBus_AddDevice: IoRegisterDeviceInterface interface name= %S)",BusDeviceData->InterfaceName.Buffer) );
 
 /* Now attach ourselves to the device stack. The return value is the next */
 /* lower down Device Object. This is where all the IRPs should be routed. */
 BusDeviceData->NextLowerDriver= IoAttachDeviceToDeviceStack (DeviceObject,PhysicalDeviceObject);
 /* Test if our attach was successful, exit if not. */
 if(!BusDeviceData->NextLowerDriver)
 {
  PPJOY_DBGPRINT (FILE_PPJOYBUS|PPJOY_ERROR, ("PPJoyBus_AddDevice: IoAttachDeviceToDeviceStack failed status= 0x%x)",ntStatus) );
  ntStatus= STATUS_NO_SUCH_DEVICE;

  PPJoyBus_WriteEventLog (PPJ_MSG_ERRORBUSATTACH,&ntStatus,sizeof(ntStatus),L"");
  RtlFreeUnicodeString (&BusDeviceData->InterfaceName);
  goto ExitDeleteDevice;
 }

 /* Save important pointers in our DeviceExtenstion for later use. */
 BusDeviceData->DriverObject= DriverObject;
 BusDeviceData->Self= DeviceObject;
 BusDeviceData->UnderlyingPDO= PhysicalDeviceObject;

 /* Initialise per DeviceObject objects */
 InitializeListHead (&BusDeviceData->JoystickList);
 KeInitializeEvent (&BusDeviceData->RemoveEvent,SynchronizationEvent,FALSE);

 /* Read configuration options from the registry */
 PPJoyBus_ReadOptionsFromReg (DeviceObject);

 /* Read persistent joystick device data from the registry and create PDOs */
 /* This call can possibly move to the DriverEntry routine???              */
 PPJoyBus_CreateFromRegistry (DeviceObject);

 /* Done initializing, clear flag. Should be the final step in AddDevice.  */
 DeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;
 goto ExitNoDelete;

ExitDeleteDevice:
 IoDeleteDevice (DeviceObject);

ExitNoDelete:
 PPJOY_EXITPROC (FILE_PPJOYBUS|PPJOY_FEXIT_STATUSOK, "PPJoyBus_AddDevice",ntStatus);

 return ntStatus;
}