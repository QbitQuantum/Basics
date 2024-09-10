NTSTATUS
USBSTOR_SendReadWrite(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp,
    IN ULONG RetryCount)
{
    UFI_READ_WRITE_CMD Cmd;
    PPDO_DEVICE_EXTENSION PDODeviceExtension;
    PCDB pCDB;
    ULONG BlockCount, Temp;
    PIO_STACK_LOCATION IoStack;
    PSCSI_REQUEST_BLOCK Request;

    //
    // get current stack location
    //
    IoStack = IoGetCurrentIrpStackLocation(Irp);

    //
    // get request block
    //
    Request = (PSCSI_REQUEST_BLOCK)IoStack->Parameters.Others.Argument1;

    //
    // get SCSI command data block
    //
    pCDB = (PCDB)Request->Cdb;

    //
    // get PDO device extension
    //
    PDODeviceExtension = (PPDO_DEVICE_EXTENSION)DeviceObject->DeviceExtension;

    //
    // informal debug print
    //
    DPRINT("USBSTOR_SendReadWrite DataTransferLength %lu, BlockLength %lu\n", Request->DataTransferLength, PDODeviceExtension->BlockLength);

    //
    // sanity check
    //
    ASSERT(PDODeviceExtension->BlockLength);

    //
    // block count
    //
    BlockCount = Request->DataTransferLength / PDODeviceExtension->BlockLength;

    //
    // initialize read cmd
    //
    RtlZeroMemory(&Cmd, sizeof(UFI_READ_WRITE_CMD));
    Cmd.Code = pCDB->AsByte[0];
    Cmd.LUN = (PDODeviceExtension->LUN & MAX_LUN);
    Cmd.ContiguousLogicBlocksByte0 = pCDB->CDB10.TransferBlocksMsb;
    Cmd.ContiguousLogicBlocksByte1 = pCDB->CDB10.TransferBlocksLsb;
    Cmd.LogicalBlockByte0 = pCDB->CDB10.LogicalBlockByte0;
    Cmd.LogicalBlockByte1 = pCDB->CDB10.LogicalBlockByte1;
    Cmd.LogicalBlockByte2 = pCDB->CDB10.LogicalBlockByte2;
    Cmd.LogicalBlockByte3 = pCDB->CDB10.LogicalBlockByte3;

    //
    // sanity check
    //
    Temp = (Cmd.ContiguousLogicBlocksByte0 << 8 | Cmd.ContiguousLogicBlocksByte1);
    ASSERT(NTOHL(Temp == BlockCount));

    DPRINT("USBSTOR_SendReadWrite BlockAddress %x%x%x%x BlockCount %lu BlockLength %lu\n", Cmd.LogicalBlockByte0, Cmd.LogicalBlockByte1, Cmd.LogicalBlockByte2, Cmd.LogicalBlockByte3, BlockCount, PDODeviceExtension->BlockLength);

    //
    // send request
    //
    return USBSTOR_SendRequest(DeviceObject, Irp, UFI_READ_WRITE_CMD_LEN, (PUCHAR)&Cmd, Request->DataTransferLength, (PUCHAR)Request->DataBuffer, RetryCount);
}