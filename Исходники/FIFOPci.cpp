/*}*/
#else /*{USE_KERNEL_PLUGIN*/
void FIFOPCI_ISR(void)
{
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  int NoOfWrDwords, MaxWriteData;
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* Indicate entering the FIFO ISR ;
   * EdenPCI_WriteDWORD(2,0x32C,1); */
  /* If we already started */
  if (FALSE == gbFIFOStartFlag)
  {	/* The FIFO should not be empty in this point */
     if ((EdenPCI_ReadDWORD(AD_PCI_BAR2, FIFO_STS_REG) & 0x1F) == FIFO_EMPTY)
     {
	EdenPCISystem_INTRDisable(LOCAL_FIFO);
	/* Q2RTApplication->GetMachineManager()->GetMachineSequencer()->GetPrintControlInstance()->Stop();
	 * CQLog::Write(LOG_TAG_PRINT,"FIFO underrun error"); */
	gUnderrunErrorCounter++;
	bFIFOUnderrunError = 1;
	return;
     }
  }
  if (BufferSizeForIntr <= 0)
  {
     EdenPCISystem_INTRDisable(LOCAL_FIFO);
     return;
  }
  MaxWriteData = ((FALSE == gbFIFOStartFlag) ? MAX_FIFO_AVAIL : MAX_FIFO_SIZE - 10);
  NoOfWrDwords = FIFOPCI_WriteDWORD(BufferForIntrPtr, MIN(MaxWriteData, BufferSizeForIntr));
  /* When we are first full since last write request , trigger the full event */
  if (TRUE == gbFIFOStartFlag)
  {
     gbFIFOStartFlag = FALSE;
     gFIFOFullEvent.SetEvent();
  }

  BufferForIntrPtr += NoOfWrDwords;
  BufferSizeForIntr -= NoOfWrDwords;
  if(BufferSizeForIntr <= 0) EdenPCISystem_INTRDisable(LOCAL_FIFO);
  /* Indicate exit from the FIFO ISR ;
   * EdenPCI_WriteDWORD(2,0x32C,0);*/
}/* FIFOPCI_ISR */