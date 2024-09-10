RecVolumes5::RecVolumes5()
{
  RealReadBuffer=NULL;

  DataCount=0;
  RecCount=0;
  TotalCount=0;
  RecBufferSize=0;

  for (uint I=0;I<ASIZE(ThreadData);I++)
  {
    ThreadData[I].RecRSPtr=this;
    ThreadData[I].RS=NULL;
  }
#ifdef RAR_SMP
  RecThreadPool=CreateThreadPool();
#endif

  RealBuf=NULL; // Might be needed in case of exception.
  RealBuf=new byte[TotalBufferSize+SSE_ALIGNMENT];
  Buf=(byte *)ALIGN_VALUE(RealBuf,SSE_ALIGNMENT);
}