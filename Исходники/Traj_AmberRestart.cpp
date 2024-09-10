/** Check for an integer (I5) followed by 0-2 scientific floats (E15.7) */
bool Traj_AmberRestart::ID_TrajFormat(CpptrajFile& fileIn) {
  // Assume file set up for read
  if (fileIn.OpenFile()) return false;
  bool isRestart = false;
  if ( fileIn.NextLine() !=0 ) { // Title
    const char* ptr = fileIn.NextLine(); // Natom [time [temp]]
    if (ptr != 0) {
      int i0;
      double D[3];
      int nread = sscanf(ptr, "%5i%15lf%15lf%lf", &i0, D, D+1, D+2);
      if (nread > 0 && nread < 4) {
        // Read at least 3 12.7 coordinates from next line.
        ptr = fileIn.NextLine();
        if (ptr != 0) {
          nread = sscanf(ptr, "%12lf%12lf%12lf", D, D+1, D+2);
          if (nread == 3)
            isRestart = true;
        }
      }
    }
  }
  fileIn.CloseFile();
  return isRestart;
}