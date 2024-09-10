static NTSTATUS
VfatVerify (PVFAT_IRP_CONTEXT IrpContext)
/*
 * FUNCTION: Verify the filesystem
 */
{
  PDEVICE_OBJECT DeviceToVerify;
  NTSTATUS Status = STATUS_SUCCESS;
  FATINFO FatInfo;
  BOOLEAN RecognizedFS;
  PDEVICE_EXTENSION DeviceExt = IrpContext->DeviceExt;

  DPRINT("VfatVerify(IrpContext %p)\n", IrpContext);

  DeviceToVerify = IrpContext->Stack->Parameters.VerifyVolume.DeviceObject;
  Status = VfatBlockDeviceIoControl(DeviceToVerify,
                                    IOCTL_DISK_CHECK_VERIFY,
                                    NULL,
                                    0,
                                    NULL,
                                    0,
                                    TRUE);
  DeviceToVerify->Flags &= ~DO_VERIFY_VOLUME;
  if (!NT_SUCCESS(Status) && Status != STATUS_VERIFY_REQUIRED)
    {
      DPRINT("VfatBlockDeviceIoControl() failed (Status %lx)\n", Status);
      Status = STATUS_WRONG_VOLUME;
    }
  else
    {
      Status = VfatHasFileSystem(DeviceToVerify, &RecognizedFS, &FatInfo);
      if (!NT_SUCCESS(Status) || RecognizedFS == FALSE)
        {
          Status = STATUS_WRONG_VOLUME;
        }
      else if (sizeof(FATINFO) == RtlCompareMemory(&FatInfo, &DeviceExt->FatInfo, sizeof(FATINFO)))
        {
          /*
           * FIXME:
           *   Preformated floppy disks have very often a serial number of 0000:0000.
           *   We should calculate a crc sum over the sectors from the root directory as secondary volume number.
           *   Each write to the root directory must update this crc sum.
           */

        }
      else
        {
          Status = STATUS_WRONG_VOLUME;
        }
     }

  return Status;
}