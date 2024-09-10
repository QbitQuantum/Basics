/*-------------------------------------------------------*/
PIORB NEAR PreProcessIORBs (NPA npA, NPU npU, PPIORB ppFirstIORB)
{
  PIORB  pIORB, pIORBPrev, pIORBNext;
  USHORT Cmd;

#define CmdCode (Cmd >> 8)
#define CmdModifier (UCHAR)(Cmd & 0xFF)

  pIORB     = *ppFirstIORB;
  pIORBPrev = 0;

  do {
    pIORBNext = (pIORB->RequestControl & IORB_CHAIN) ? pIORB->pNxtIORB : 0;
    Cmd = REQ (pIORB->CommandCode, pIORB->CommandModifier);

    if ((Cmd == REQ (IOCC_ADAPTER_PASSTHRU, IOCM_EXECUTE_CDB)) ||
	(CmdCode == IOCC_CONFIGURATION) ||
	(CmdCode == IOCC_RESOURCE)	||
	(CmdCode == IOCC_DEVICE_CONTROL)) {

      if (pIORBPrev) {
	pIORBPrev->pNxtIORB = pIORBNext;
      } else {
	*ppFirstIORB = pIORBNext;
      }

      if (CmdCode == IOCC_RESOURCE) Cmd = 10 + CmdModifier;
      if (CmdCode == IOCC_CONFIGURATION) Cmd = 8 + CmdModifier;
      if (CmdCode == IOCC_ADAPTER_PASSTHRU) {
	PCHAR SCSICmd = ((PIORB_ADAPTER_PASSTHRU)pIORB)->pControllerCmd;

	Cmd = 0;
	if ((SCSICmd[0] == SCSI_START_STOP_UNIT) && (SCSICmd[4] == 2))
	  Cmd = IOCM_EJECT_MEDIA;
      }

      switch (CmdModifier) {
	case 9 /* IOCM_GET_DEVICE_TABLE */ :
	  GetDeviceTable (pIORB); break;

	case 10 /* IOCM_COMPLETE_INIT */ :
	  CompleteInit (npA); break;

	case 11 /* IOCM_REPORT_RESOURCES */ :
	  GetUnitResources (npA, pIORB); break;

	case IOCM_SUSPEND :
	  SuspendIORBReq (npA, pIORB); break;

	case IOCM_RESUME :
	  ResumeIORBReq (npA, pIORB); break;

	case IOCM_GET_QUEUE_STATUS :
	  GetQueueStatus (npA, pIORB); break;

	case IOCM_EJECT_MEDIA :
	case IOCM_LOCK_MEDIA :
	case IOCM_UNLOCK_MEDIA :
	  ProcessLockUnlockEject (npU, pIORB, CmdModifier); break;

	default:
	  pIORB->Status   |= IORB_ERROR;
	  pIORB->ErrorCode = IOERR_CMD_NOT_SUPPORTED;
      }

      if (CmdModifier != IOCM_SUSPEND) {
	pIORB->Status |= IORB_DONE;

	if (pIORB->RequestControl & IORB_ASYNC_POST)
	  ((PIORBNotify)pIORB->NotifyAddress) (pIORB);
      }
      continue;
    }
    pIORBPrev = pIORB;
  } while (pIORB = pIORBNext);

  if (pIORBPrev)
    pIORBPrev->pNxtIORB = 0;

  return (pIORBPrev);
}