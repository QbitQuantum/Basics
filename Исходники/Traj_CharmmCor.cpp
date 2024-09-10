bool Traj_CharmmCor::ID_TrajFormat(CpptrajFile& fileIn) {
  // File must already be set up for read.
  if (fileIn.OpenFile()) return false;
  bool isCor = false;
  const char* ptr = fileIn.NextLine();
  // Must be at least 1 title line denoted with '*'
  if (ptr != 0 && *ptr == '*') {
    // Scan past all title lines
    while (ptr != 0 && *ptr == '*') ptr = fileIn.NextLine();
    if (ptr != 0) {
      // Next line must be # atoms ONLY
      int ibuf[2];
      if (sscanf(ptr, "%i %i", ibuf, ibuf+1) == 1)
        // make sure it was a valid integer
        isCor = (ibuf[0] > 0);
    }
  }
  fileIn.CloseFile();
  return isCor;
}