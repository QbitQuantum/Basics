unsigned int InitAudio(unsigned int Rate,unsigned int Latency)
{
  static const int PagePort[8] = { 0x87,0x83,0x81,0x82,-1,0x8B,0x89,0x8A };
  int J,TotalBuf;
  char *P;

  /* Disable audio if was initialized */
  TrashAudio();

  /* If turning audio off, drop out */
  if(!Rate) return(1);

  /* If Rate is out of range, fall out */
  if((Rate<8192)||(Rate>44100)) return(0);

  /* Default values */
  SBPort    = 0x220;
  SBIRQ     = 7;
  SBDMA     = 1;
  SBIRQBusy = 0;
  SBWrite   = 0;
  SBRead    = 0;

  /* Get SoundBlaster Port#,IRQ#,DMA# */
  if(P=getenv("BLASTER"))
    while(*P)
      switch(toupper(*P++))
      {
        case 'A': SBPort=strtol(P,0,16);break;
        case 'D': SBDMA=strtol(P,0,16);break;
        case 'I': SBIRQ=strtol(P,0,16);break;
      }

  /* IRQ# = 0,1,2,3,4,5,6,7, DMA# = 0,1,2,3 */
  if((SBIRQ>7)||(SBDMA>3)) return(0);

  /* Reset DSP */
  outp(SBPort+0x06,0x01); /* Set the reset flag   */
  delay(100);             /* Wait for 100ms       */
  outp(SBPort+0x06,0x00); /* Clear the reset flag */

  /* Wait for READY status */
  for(J=100;J&&!(inp(SBPort+0x0E)&0x80);J--);
  if(!J) return(0);
  for(J=100;J&&(ReadDSP()!=0xAA);J--);
  if(!J) return(0);

  /* Allocate low memory for DMA buffer */
  TotalBuf=(Rate*Latency/1000/SND_BUFSIZE)*SND_BUFSIZE;
  if(TotalBuf<SND_BUFSIZE) TotalBuf=SND_BUFSIZE;
  SBBuffers=TotalBuf/SND_BUFSIZE;
  SBSegment=GetSegment(TotalBuf*sizeof(sample)*2/16+4);
  if(!SBSegment) return(0);
  J=SBSegment*16;
  SBBuffer=(unsigned char *)J;
  if((J>>16)!=((J+TotalBuf-1)>>16)) SBBuffer+=TotalBuf;
  memset(SBBuffer,0,TotalBuf*sizeof(sample));

  /* Interrupts off */
  _disable();

  /* Save old interrupt vector */
  IRQ5Old=(void (interrupt *)())_dos_getvect(SBIRQ+8);
  /* Install new interrupt vector */
  _dos_setvect(SBIRQ+8,IRQ5Handler);
  /* Enable the SoundBlaster IRQ */
  outp(0x21,inp(0x21)&~(1<<SBIRQ));

  /* Disable DMA channel */
  outp(0x0A,SBDMA|0x04);
  /* Clear byte pointer flip-flop */
  outp(0x0C,0x00);
  /* Auto-initialized playback mode */
  outp(0x0B,SBDMA|0x58);
  /* Write DMA offset and transfer length */
  J=SBDMA<<1;
  outp(J,(int)SBBuffer&0xFF);
  outp(J,((int)SBBuffer>>8)&0xFF);
  outp(J+1,(TotalBuf-1)&0xFF);
  outp(J+1,((TotalBuf-1)>>8)&0xFF);
  /* Write DMA page */
  outp(PagePort[SBDMA],((int)SBBuffer>>16)&0xFF);
  /* Enable DMA channel */
  outp(0x0A,SBDMA);

  /* Enable interrupts */
  _enable();

  /* Set sampling rate */
  WriteDSP(0x40);
  WriteDSP((65536L-(256000000L/Rate))/256);
  /* Set DMA transfer size */
  WriteDSP(0x48);
  WriteDSP((SND_BUFSIZE-1)&0xFF);
  WriteDSP((SND_BUFSIZE-1)>>8);
  /* Run auto-initialized 8bit DMA */
  WriteDSP(0x90);
  /* Speaker enabled */
  WriteDSP(0xD1);

  /* Done */
  return(SndRate=Rate);
}