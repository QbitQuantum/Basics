//---------------------------------------------------------------------------
// TImageBuffer constructor
//
__fastcall TImageBuffer::TImageBuffer(int Size, int Count) {

  FAllocSister = NULL;

  Sync = new TMultiReadExclusiveWriteSynchronizer();

  ChunkSize = Size;
  ChunkCount = 1 << (int)Ceil(Log2(Count));
  IndexMask = ChunkCount - 1;
  Chunks = new TBufferChunk *[ChunkCount];
  ChunkStates = new TBufferChunkState [ChunkCount];

  NextReadChunkIndex = NextWriteChunkIndex = 0;

  // Create all the buffer chunks
  for (unsigned n = 0; n < ChunkCount; n++) {
    Chunks[n] = new TBufferChunk(ChunkSize, n);
    ChunkStates[n] = csFree;
  }  // for (unsigned n = 0; n < nChunkCount; n++)

  // Initialize our event objects
  ReadChunkReady  = new TEvent(NULL, true, false, IntToHex((int)this, 8) + ":Read");
  if (!ReadChunkReady->Handle)
    throw ESelfImageSystemError("Failed to create image buffer read event object.");
  WriteChunkReady = new TEvent(NULL, true, false, IntToHex((int)this, 8) + ":Write");
  if (!WriteChunkReady->Handle)
    throw ESelfImageSystemError("Failed to create image buffer write event object.");

}  // TImageBuffer::TImageBuffer(int nChunkSize, int nChunkCount)