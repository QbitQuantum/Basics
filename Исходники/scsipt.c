/*
 * fills in a pDrive structure with information from a SCSI_INQUIRY
 * and obtains the ha:tgt:lun values via IOCTL_SCSI_GET_ADDRESS
 */
void SPT_GetDriveInformation( BYTE i, SPT_DRIVE *pDrive )
{
  HANDLE fh;
  char buf[1024];
  BOOLEAN status;
  PSCSI_PASS_THROUGH_DIRECT_WITH_BUFFER pswb;
  PSCSI_ADDRESS pscsiAddr;
  ULONG length, returned;
  BYTE inqData[100];

#ifdef _DEBUG_SCSIPT
  dbprintf( "AKRip32: SCSIPT: Checking drive %c:\n", 'A'+i );
#endif

  fh = GetFileHandle( i );

  if ( fh == INVALID_HANDLE_VALUE )
    {
#ifdef _DEBUG_SCSIPT
      dbprintf( "       : fh == INVALID_HANDLE_VALUE\n" );
#endif
      return;
    }

#ifdef _DEBUG_SCSIPT
  dbprintf( "       : Index %d: fh == %08X\n", i, fh );
#endif


  /*
   * Get the drive inquiry data
   */
  ZeroMemory( &buf, 1024 );
  ZeroMemory( inqData, 100 );
  pswb                      = (PSCSI_PASS_THROUGH_DIRECT_WITH_BUFFER)buf;
  pswb->spt.Length          = sizeof(SCSI_PASS_THROUGH);
  pswb->spt.CdbLength       = 6;
  pswb->spt.SenseInfoLength = 24;
  pswb->spt.DataIn          = SCSI_IOCTL_DATA_IN;
  pswb->spt.DataTransferLength = 100;
  pswb->spt.TimeOutValue    = 2;
  pswb->spt.DataBuffer      = inqData;
  pswb->spt.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER,ucSenseBuf );
  pswb->spt.Cdb[0]          = 0x12;
  pswb->spt.Cdb[4]          = 100;

  length = sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER);
  status = DeviceIoControl( fh,
			    IOCTL_SCSI_PASS_THROUGH_DIRECT,
			    pswb,
			    length,
			    pswb,
			    length,
			    &returned,
			    NULL );

  if ( !status )
    {
      CloseHandle( fh );
#ifdef _DEBUG_SCSIPT
      dbprintf( "AKRip32: SCSIPT: Error DeviceIoControl() -> %d\n",
		GetLastError() );
#endif
      return;
    }

  memcpy( pDrive->inqData, inqData, 36 );

  /*
   * get the address (path/tgt/lun) of the drive via IOCTL_SCSI_GET_ADDRESS
   */
  ZeroMemory( &buf, 1024 );
  pscsiAddr = (PSCSI_ADDRESS)buf;
  pscsiAddr->Length = sizeof(SCSI_ADDRESS);
  if ( DeviceIoControl( fh, IOCTL_SCSI_GET_ADDRESS, NULL, 0,
			pscsiAddr, sizeof(SCSI_ADDRESS), &returned,
			NULL ) )
    {
#ifdef _DEBUG_SCSIPT
      dbprintf( "Device %c: Port=%d, PathId=%d, TargetId=%d, Lun=%d\n",
		(char)i+'A', pscsiAddr->PortNumber, pscsiAddr->PathId,
		pscsiAddr->TargetId, pscsiAddr->Lun );
#endif
      pDrive->bUsed     = TRUE;
      pDrive->ha        = pscsiAddr->PortNumber;
      pDrive->tgt       = pscsiAddr->TargetId;
      pDrive->lun       = pscsiAddr->Lun;
      pDrive->driveLetter = i;
      pDrive->hDevice   = INVALID_HANDLE_VALUE;
    }
  else
    {
      pDrive->bUsed     = FALSE;
#ifdef _DEBUG_SCSIPT
      dbprintf( "AKRip32: SPTI: Device %s: Error DeviceIoControl(): %d\n", (char)i+'A', GetLastError() );
#endif
      return;
    }

#ifdef _DEBUG_SCSIPT
  dbprintf( "AKRip32: SPTI: Adding drive %c: (%d:%d:%d)\n", 'A'+i,
	    pDrive->ha, pDrive->tgt, pDrive->lun );
#endif

  CloseHandle( fh );
}