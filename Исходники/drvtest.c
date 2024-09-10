/******************************************************************************
 *                            Driver unload handler                           *
 ******************************************************************************/
static VOID DDKAPI
my_unload(PDRIVER_OBJECT DriverObject)
{
  ANSI_STRING SymbolicLinkNameA;
  UNICODE_STRING SymbolicLinkNameW;
  DbgPrint("DriverUnload called\r\n");

  PsSetCreateProcessNotifyRoutine(create_process_watcher, TRUE);
  PsRemoveLoadImageNotifyRoutine(load_image_watcher);

  RtlInitString(&SymbolicLinkNameA, MY_DOSDEVICE_NAME);
  RtlAnsiStringToUnicodeString(&SymbolicLinkNameW, &SymbolicLinkNameA, TRUE);

  IoDeleteSymbolicLink(&SymbolicLinkNameW);
  IoDeleteDevice(DriverObject->DeviceObject);

  for (int i = 0; i < ENT_CNT; ++i)
    if(g_proc_table[i].pid)
      DbgPrint("Registered process stays: %d\r\n", g_proc_table[i].pid);
}