RecVolumes3::RecVolumes3()
{
  Buf.Alloc(TotalBufferSize);
  memset(SrcFile,0,sizeof(SrcFile));
#ifdef RAR_SMP
  RSThreadPool=CreateThreadPool();
#endif
}