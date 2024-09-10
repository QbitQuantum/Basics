VOID
VIOSerialPortSymbolicNameWork(
    IN WDFWORKITEM  WorkItem
    )
{

    PRAWPDO_VIOSERIAL_PORT  pdoData = RawPdoSerialPortGetData(WorkItem);
    PVIOSERIAL_PORT         pport = pdoData->port;
    UNICODE_STRING          deviceUnicodeString = {0};
    NTSTATUS                status  = STATUS_SUCCESS;

    DECLARE_UNICODE_STRING_SIZE(symbolicLinkName, 256);

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "--> %s\n", __FUNCTION__);

    do
    {
        if (pport->NameString.Buffer)
        {
           status = RtlAnsiStringToUnicodeString( &deviceUnicodeString,
                                 &pport->NameString,
                                 TRUE
                                 );
           if (!NT_SUCCESS(status))
           {
              TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP,
                "RtlAnsiStringToUnicodeString failed 0x%x\n", status);
              break;
           }

           TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP,"deviceUnicodeString = %ws\n", deviceUnicodeString.Buffer);

           status = RtlUnicodeStringPrintf(
                                 &symbolicLinkName,
                                 L"%ws%ws",
                                 L"\\DosDevices\\",
                                 deviceUnicodeString.Buffer
                                 );
           if (!NT_SUCCESS(status))
           {
              TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP,
                "RtlUnicodeStringPrintf failed 0x%x\n", status);
              break;
           }

           status = WdfDeviceCreateSymbolicLink(
                                 pport->Device,
                                 &symbolicLinkName
                                 );
           if (!NT_SUCCESS(status))
           {
              TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP,
                "WdfDeviceCreateSymbolicLink %ws failed 0x%x\n", &symbolicLinkName, status);
              break;
           }
        }
    } while (0);

    if (deviceUnicodeString.Buffer != NULL)
    {
        RtlFreeUnicodeString( &deviceUnicodeString );
    }
    WdfObjectDelete(WorkItem);
    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "<-- %s\n", __FUNCTION__);
}