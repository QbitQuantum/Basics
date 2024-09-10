NTSTATUS
FxDriver::OpenParametersKey(
    VOID
    )
{
    HRESULT hr;
    NTSTATUS status;
    
    PFX_DRIVER_GLOBALS FxDriverGlobals = GetDriverGlobals();
    PDRIVER_OBJECT_UM pDrvObj = GetDriverObject();
    IWudfDeviceStack* pDevStack = (IWudfDeviceStack*)pDrvObj->WudfDevStack;

    UMINT::WDF_PROPERTY_STORE_ROOT rootSpecifier;
    UMINT::WDF_PROPERTY_STORE_RETRIEVE_FLAGS flags;
    CANSI_STRING serviceNameA;
    DECLARE_UNICODE_STRING_SIZE(serviceNameW, WDF_DRIVER_GLOBALS_NAME_LEN);
    HKEY hKey;

    RtlInitAnsiString(&serviceNameA, FxDriverGlobals->Public.DriverName);
    status = RtlAnsiStringToUnicodeString(&serviceNameW,
                                          &serviceNameA,
                                          FALSE);
    if (NT_SUCCESS(status)) {
        rootSpecifier.LengthCb = sizeof(UMINT::WDF_PROPERTY_STORE_ROOT);
        rootSpecifier.RootClass = UMINT::WdfPropertyStoreRootDriverParametersKey;
        rootSpecifier.Qualifier.ParametersKey.ServiceName = serviceNameW.Buffer;
        
        flags = UMINT::WdfPropertyStoreCreateIfMissing;

        hr = pDevStack->CreateRegistryEntry(&rootSpecifier,
                                            flags,
                                            GENERIC_ALL & ~(GENERIC_WRITE | KEY_CREATE_SUB_KEY | WRITE_DAC),
                                            NULL,
                                            &hKey,
                                            NULL);
        status = FxDevice::NtStatusFromHr(pDevStack, hr);
        if (NT_SUCCESS(status)) {
            m_DriverParametersKey = hKey;
        }
    }

    return status;
}