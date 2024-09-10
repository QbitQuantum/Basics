BOOLEAN
TapeVerifyInquiry(
    IN PSCSI_INQUIRY_DATA LunInfo
    )

/*++
Routine Description:

    This routine determines if the driver should claim this device.

Arguments:

    LunInfo

Return Value:

    TRUE - driver should claim this device.
    FALSE - driver should not claim this device.

--*/

{
    PINQUIRYDATA        inquiryData;

    DebugPrint((3,"TapeVerifyInquiry: Verify Tape Inquiry Data\n"));

    inquiryData = (PVOID)LunInfo->InquiryData;

    return ((RtlCompareMemory(inquiryData->VendorId,"OVERLAND",8) == 8) &&
           ((RtlCompareMemory(inquiryData->ProductId,"_5212/5214",10) == 10) ||
           (RtlCompareMemory(inquiryData->ProductId,"_5612/5614",10) == 10)));

} // end TapeVerifyInquiry()