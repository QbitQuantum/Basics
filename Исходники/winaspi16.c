static WORD
ASPI_ExecScsiCmd(DWORD ptrPRB, UINT16 mode)
{
  SRB_ExecSCSICmd16 *lpPRB = PTR_TO_LIN( ptrPRB, mode );
  struct sg_header *sg_hd, *sg_reply_hdr;
  int	status;
  BYTE *lpBuf = 0;
  int	in_len, out_len;
  int	error_code = 0;
  int	fd;

  ASPI_DebugPrintCmd(lpPRB, mode);

  fd = ASPI_OpenDevice16(lpPRB);
  if (fd == -1) {
      WARN("Failed: could not open device. Device permissions !?\n");
      lpPRB->SRB_Status = SS_ERR;
      return SS_ERR;
  }

  sg_hd = NULL;
  sg_reply_hdr = NULL;

  lpPRB->SRB_Status = SS_PENDING;
  lpBuf = PTR_TO_LIN( lpPRB->SRB_BufPointer, mode );

  if (!lpPRB->SRB_CDBLen) {
      WARN("Failed: lpPRB->SRB_CDBLen = 0.\n");
      lpPRB->SRB_Status = SS_ERR;
      return SS_ERR;
  }

  /* build up sg_header + scsi cmd */
  if (HOST_TO_TARGET(lpPRB)) {
    /* send header, command, and then data */
    in_len = SCSI_OFF + lpPRB->SRB_CDBLen + lpPRB->SRB_BufLen;
    sg_hd = (struct sg_header *) malloc(in_len);
    memset(sg_hd, 0, SCSI_OFF);
    memcpy(sg_hd + 1, &lpPRB->CDBByte[0], lpPRB->SRB_CDBLen);
    if (lpPRB->SRB_BufLen) {
      memcpy(((BYTE *) sg_hd) + SCSI_OFF + lpPRB->SRB_CDBLen, lpBuf, lpPRB->SRB_BufLen);
    }
  }
  else {
    /* send header and command - no data */
    in_len = SCSI_OFF + lpPRB->SRB_CDBLen;
    sg_hd = (struct sg_header *) malloc(in_len);
    memset(sg_hd, 0, SCSI_OFF);
    memcpy(sg_hd + 1, &lpPRB->CDBByte[0], lpPRB->SRB_CDBLen);
  }

  if (TARGET_TO_HOST(lpPRB)) {
    out_len = SCSI_OFF + lpPRB->SRB_BufLen;
    sg_reply_hdr = (struct sg_header *) malloc(out_len);
    memset(sg_reply_hdr, 0, SCSI_OFF);
    sg_hd->reply_len = out_len;
  }
  else {
    out_len = SCSI_OFF;
    sg_reply_hdr = (struct sg_header *) malloc(out_len);
    memset(sg_reply_hdr, 0, SCSI_OFF);
    sg_hd->reply_len = out_len;
  }

  status = write(fd, sg_hd, in_len);
  if (status < 0 || status != in_len) {
      int save_error = errno;

    WARN("Not enough bytes written to scsi device bytes=%d .. %d\n", in_len, status);
    if (status < 0) {
		if (save_error == ENOMEM) {
	    MESSAGE("ASPI: Linux generic scsi driver\n  You probably need to re-compile your kernel with a larger SG_BIG_BUFF value (sg.h)\n  Suggest 130560\n");
	}
		WARN("error:= '%s'\n", strerror(save_error));
    }
    goto error_exit;
  }

  status = read(fd, sg_reply_hdr, out_len);
  if (status < 0 || status != out_len) {
    WARN("not enough bytes read from scsi device%d\n", status);
    goto error_exit;
  }

  if (sg_reply_hdr->result != 0) {
    error_code = sg_reply_hdr->result;
    WARN("reply header error (%d)\n", sg_reply_hdr->result);
    goto error_exit;
  }

  if (TARGET_TO_HOST(lpPRB) && lpPRB->SRB_BufLen) {
    memcpy(lpBuf, sg_reply_hdr + 1, lpPRB->SRB_BufLen);
  }

  /* copy in sense buffer to amount that is available in client */
  if (lpPRB->SRB_SenseLen) {
    int sense_len = lpPRB->SRB_SenseLen;
    if (lpPRB->SRB_SenseLen > 16)
      sense_len = 16;
    memcpy(SENSE_BUFFER(lpPRB), &sg_reply_hdr->sense_buffer[0], sense_len);
  }


  lpPRB->SRB_Status = SS_COMP;
  lpPRB->SRB_HaStat = HASTAT_OK;
  lpPRB->SRB_TargStat = STATUS_GOOD;

  /* now do posting */

  if (ASPI_POSTING(lpPRB) && lpPRB->SRB_PostProc) {
    TRACE("Post Routine (%x) called\n", (DWORD) lpPRB->SRB_PostProc);
    switch (mode)
    {
      case ASPI_DOS:
      {
	SEGPTR spPRB = MapLS(lpPRB);

        WOWCallback16((DWORD)lpPRB->SRB_PostProc, spPRB);
	UnMapLS(spPRB);
	break;
      }
      case ASPI_WIN16:
        WOWCallback16((DWORD)lpPRB->SRB_PostProc, ptrPRB);
	break;
    }
  }

  free(sg_reply_hdr);
  free(sg_hd);
  ASPI_DebugPrintResult(lpPRB, mode);
  return SS_COMP;

error_exit:
  if (error_code == EBUSY) {
      lpPRB->SRB_Status = SS_ASPI_IS_BUSY;
      TRACE("Device busy\n");
  }
  else {
      WARN("Failed\n");
      lpPRB->SRB_Status = SS_ERR;
  }

  /* I'm not sure exactly error codes work here
   * We probably should set lpPRB->SRB_TargStat, SRB_HaStat ?
   */
  WARN("error_exit\n");
  free(sg_reply_hdr);
  free(sg_hd);
  return lpPRB->SRB_Status;
}