int DST_InitDecoder(ebunch * D, int NrOfChannels, int SampleRate) 
{
  int  retval = 0;

  memset(D, 0, sizeof(ebunch));

  D->FrameHdr.NrOfChannels   = NrOfChannels;
  /*  64FS =>  4704 */
  /* 128FS =>  9408 */
  /* 256FS => 18816 */
  D->FrameHdr.MaxFrameLen    = (588 * SampleRate / 8); 
  D->FrameHdr.ByteStreamLen  = D->FrameHdr.MaxFrameLen   * D->FrameHdr.NrOfChannels;
  D->FrameHdr.BitStreamLen   = D->FrameHdr.ByteStreamLen * RESOL;
  D->FrameHdr.NrOfBitsPerCh  = D->FrameHdr.MaxFrameLen   * RESOL;
  D->FrameHdr.MaxNrOfFilters = 2 * D->FrameHdr.NrOfChannels;
  D->FrameHdr.MaxNrOfPtables = 2 * D->FrameHdr.NrOfChannels;

  D->FrameHdr.FrameNr = 0;
  D->StrFilter.TableType = FILTER;
  D->StrPtable.TableType = PTABLE;

  if (retval==0) 
  {
    AllocateDecMemory(D);
  }

  if (retval==0) 
  {
    retval = CCP_CalcInit(&D->StrFilter);
  }
  if (retval==0) 
  {
    retval = CCP_CalcInit(&D->StrPtable);
  }

  D->SSE2 = 0;
#if !defined(NO_SSE2) && (defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__x86_64__))
  {
    int CPUInfo[4];
#if defined(__i386__) || defined(__x86_64__)
#define cpuid(type, a, b, c, d) \
    __asm__ ("cpuid":\
    "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (type));

    cpuid(1, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
#else
    __cpuid(CPUInfo, 1);
#endif

    D->SSE2 = (CPUInfo[3] & (1L << 26)) ? 1 : 0;
  }
#endif

  return(retval);
}