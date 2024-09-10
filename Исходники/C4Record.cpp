StdBuf C4Playback::ReWriteBinary() {
  const int OUTPUT_GROW = 16 * 1024;
  StdBuf Output;
  int iPos = 0;
  bool fFinished = false;
  uint32_t iFrame = 0;
  for (chunks_t::const_iterator i = chunks.begin();
       !fFinished && i != chunks.end(); i++) {
    // Check frame difference
    if (i->Frame - iFrame < 0 || i->Frame - iFrame > 0xff)
      LogF(
          "ERROR: Invalid frame difference between chunks (0-255 allowed)! "
          "Data will be invalid!");
    // Pack data
    StdBuf Chunk;
    try {
      switch (i->Type) {
        case RCT_Ctrl:
          Chunk = DecompileToBuf<StdCompilerBinWrite>(*i->pCtrl);
          break;
        case RCT_CtrlPkt:
          Chunk = DecompileToBuf<StdCompilerBinWrite>(*i->pPkt);
          break;
        case RCT_End:
          fFinished = true;
          break;
        default:  // debugrec
          if (i->pDbg) Chunk = DecompileToBuf<StdCompilerBinWrite>(*i->pDbg);
          break;
      }
    } catch (StdCompiler::Exception *pEx) {
      LogF("Record: Binary unpack error: %s", pEx->Msg.getData());
      delete pEx;
      return StdBuf();
    }
    // Grow output
    while (Output.getSize() - iPos <
           sizeof(C4RecordChunkHead) + Chunk.getSize())
      Output.Grow(OUTPUT_GROW);
    // Write header
    C4RecordChunkHead *pHead = getMBufPtr<C4RecordChunkHead>(Output, iPos);
    pHead->Type = i->Type;
    pHead->iFrm = i->Frame - iFrame;
    iPos += sizeof(C4RecordChunkHead);
    iFrame = i->Frame;
    // Write chunk
    Output.Write(Chunk, iPos);
    iPos += Chunk.getSize();
  }
  Output.SetSize(iPos);
  return Output;
}