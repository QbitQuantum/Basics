BOOLEAN
MpHwStartIo(
__in                PVOID                DeviceExtension,  // Adapter device-object extension from port driver.
__inout __deref     PSCSI_REQUEST_BLOCK  pSrb
)
{
    KIRQL                   lowest_assumed_irql = PASSIVE_LEVEL;
    ResultType              Result = ResultDone;
    pHW_HBA_EXT             pHBAExt = (pHW_HBA_EXT)DeviceExtension;
#ifdef USE_SCSIPORT
    UCHAR                   PathId = pSrb->PathId;
    UCHAR                   TargetId = pSrb->TargetId;
    UCHAR                   Lun = pSrb->Lun;
#endif

    KdPrint2(("PhDskMnt::MpHwStartIo:  pHBAExt = 0x%p, pSrb = 0x%p, Path=%i, Target=%i, Lun=%i, IRQL=%i\n",
        pHBAExt,
        pSrb,
        (int)pSrb->PathId,
        (int)pSrb->TargetId,
        (int)pSrb->Lun,
        KeGetCurrentIrql()));

    pSrb->SrbStatus = SRB_STATUS_PENDING;
    pSrb->ScsiStatus = SCSISTAT_GOOD;

    ImScsiCompletePendingSrbs(pHBAExt, &lowest_assumed_irql);

    _InterlockedExchangeAdd((volatile LONG *)&pHBAExt->SRBsSeen, 1);   // Bump count of SRBs encountered.

    // Next, if true, will cause port driver to remove the associated LUNs if, for example, devmgmt.msc is asked "scan for hardware changes."
    //if (pHBAExt->bDontReport)
    //{                       // Act as though the HBA/path is gone?
    //    pSrb->SrbStatus = SRB_STATUS_NO_DEVICE;
    //    goto done;
    //}

    switch (pSrb->Function)
    {
    case SRB_FUNCTION_IO_CONTROL:
        ScsiIoControl(pHBAExt, pSrb, &Result, &lowest_assumed_irql);
        break;

    case SRB_FUNCTION_EXECUTE_SCSI:
        if (pSrb->Cdb[0] == SCSIOP_REPORT_LUNS)
        {
            ScsiOpReportLuns(pHBAExt, pSrb, &lowest_assumed_irql);
        }
        else
        {
            ScsiExecute(pHBAExt, pSrb, &Result, &lowest_assumed_irql);
        }
        break;

    case SRB_FUNCTION_RESET_LOGICAL_UNIT:
        DbgPrint("PhDskMnt::MpHwStartIo: SRB_FUNCTION_RESET_LOGICAL_UNIT.\n");
        pSrb->SrbStatus = ScsiResetLun(pHBAExt, pSrb);
        break;

    case SRB_FUNCTION_RESET_DEVICE:
        DbgPrint("PhDskMnt::MpHwStartIo: SRB_FUNCTION_RESET_DEVICE.\n");
        pSrb->SrbStatus = ScsiResetDevice(pHBAExt, pSrb);
        break;

    case SRB_FUNCTION_RESET_BUS:
        DbgPrint("PhDskMnt::MpHwStartIo: SRB_FUNCTION_RESET_BUS.\n");
        pSrb->SrbStatus = MpHwResetBus(pHBAExt, pSrb->PathId);
        break;

    case SRB_FUNCTION_PNP:
        ScsiPnP(pHBAExt, (PSCSI_PNP_REQUEST_BLOCK)pSrb, &lowest_assumed_irql);
        break;

    case SRB_FUNCTION_POWER:
        KdPrint(("PhDskMnt::MpHwStartIo: SRB_FUNCTION_POWER.\n"));
        // Do nothing.
        pSrb->SrbStatus = SRB_STATUS_SUCCESS;

        break;

    case SRB_FUNCTION_SHUTDOWN:
        KdPrint(("PhDskMnt::MpHwStartIo: SRB_FUNCTION_SHUTDOWN.\n"));
        // Do nothing.
        pSrb->SrbStatus = SRB_STATUS_SUCCESS;

        break;

    default:
        KdPrint(("PhDskMnt::MpHwStartIo: Unknown pSrb Function = 0x%X\n", pSrb->Function));

        //StorPortLogError(pHBAExt, pSrb, pSrb->PathId, pSrb->TargetId, pSrb->Lun, SP_PROTOCOL_ERROR, 0x0200 | pSrb->Cdb[0]);

        ScsiSetCheckCondition(pSrb, SRB_STATUS_ERROR, SCSI_SENSE_ILLEGAL_REQUEST, SCSI_ADSENSE_ILLEGAL_COMMAND, 0);

        break;

    } // switch (pSrb->Function)

    if (Result == ResultDone)
    {                         // Complete now?
#ifdef USE_SCSIPORT
        KdPrint2(("PhDskMnt::MpHwStartIo sending 'RequestComplete', 'NextRequest' and 'NextLuRequest' to ScsiPort.\n"));
        ScsiPortNotification(RequestComplete, pHBAExt, pSrb);
        ScsiPortNotification(NextRequest, pHBAExt);
        ScsiPortNotification(NextLuRequest, pHBAExt, 0, 0, 0);
#endif
#ifdef USE_STORPORT
        KdPrint2(("PhDskMnt::MpHwStartIo sending 'RequestComplete' to port StorPort.\n"));
        StorPortNotification(RequestComplete, pHBAExt, pSrb);
#endif
    }
    else
    {
#ifdef USE_SCSIPORT
        _InterlockedExchangeAdd((volatile LONG*)&pHBAExt->WorkItems, 1);

        KdPrint2(("PhDskMnt::MpHwStartIo sending 'RequestTimerCall' and 'NextLuRequest' to ScsiPort.\n"));
        ScsiPortNotification(RequestTimerCall, pHBAExt, MpHwTimer, (ULONG)1);
        ScsiPortNotification(NextLuRequest, pHBAExt, PathId, TargetId, Lun);
        ScsiPortNotification(NextLuRequest, pHBAExt, 0, 0, 0);
#endif
    }

    KdPrint2(("PhDskMnt::MpHwStartIo End.\n"));

    return TRUE;
}                                                     // End MpHwStartIo().