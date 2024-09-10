// Traj_AmberCoord::ID_TrajFormat()
bool Traj_AmberCoord::ID_TrajFormat(CpptrajFile& fileIn) {
  // File must already be set up for read
  if (fileIn.OpenFile()) return false;
  if (fileIn.NextLine()==0) return false; // Title
  std::string buffer2 = fileIn.GetLine(); // REMD header/coords
  fileIn.CloseFile();
  // Check if second line contains REMD/HREMD, Amber Traj with REMD header
  if ( IsRemdHeader( buffer2.c_str() ) ) {
    if (debug_>0) mprintf("  AMBER TRAJECTORY with (H)REMD header.\n");
    headerSize_ = REMD_HEADER_SIZE + (size_t)fileIn.IsDos();
    tStart_ = 33; // 42 - 8 - 1
    tEnd_   = 41; // 42 - 1
    return true;
  }
  // TODO: Read these in as indices instead of temperatures
  if ( IsRxsgldHeader( buffer2.c_str() ) ) {
    mprintf("  AMBER TRAJECTORY with RXSGLD header.\n");
    headerSize_ = RXSGLD_HEADER_SIZE + (size_t)fileIn.IsDos();
    tStart_ = 35; // 44 - 8 - 1
    tEnd_   = 43; // 44 - 1
    return true;
  }
  // Check if we can read 3, 6, 9, or 10 coords (corresponding to 1, 2, 3 or
  // > 3 atoms) of width 8; Amber trajectory.
  float TrajCoord[10];
  int nscan = sscanf(buffer2.c_str(), "%8f%8f%8f%8f%8f%8f%8f%8f%8f%8f",
                     TrajCoord,   TrajCoord+1, TrajCoord+2, TrajCoord+3,
                     TrajCoord+4, TrajCoord+5, TrajCoord+6, TrajCoord+7,
                     TrajCoord+8, TrajCoord+9);
  if (nscan == 3 || nscan == 6 || nscan == 9 || nscan == 10)
  {
    if (debug_>0) mprintf("  AMBER TRAJECTORY file\n");
    return true;
  }
  return false;
}