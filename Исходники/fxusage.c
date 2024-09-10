VOID
HalReportResourceUsage(
    VOID
    )
/*++

Routine Description:

Arguments:

Return Value:

--*/
{

    ANSI_STRING     AHalName;
    UNICODE_STRING  UHalName;

    //
    // Report IO space usage
    // for HAL/system resources
    //

    RtlInitAnsiString (&AHalName, HalName);
    RtlAnsiStringToUnicodeString (&UHalName, &AHalName, TRUE);

    HalpReportResourceUsage (
        &UHalName,
        PCIBus
    );

    //RtlFreeUnicodeString (&UHalName);

    //
    // Now create the registry keys
    // used to log errors if they
    // do not already exist
    //

    HalpCreateLogKeys();

}