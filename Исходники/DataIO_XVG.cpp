bool DataIO_XVG::ID_DataFormat(CpptrajFile& infile) {
  if (infile.OpenFile()) return false;
  const char* ptr = infile.NextLine();
  while (ptr != 0 && ptr[0] == '#') {
    const char* cc = ptr;
    while (*cc != '\0') {
      if (*cc == 'G') {
        if ( cc[2] == 'R' && cc[4]  == 'O' && cc[6]  == 'M' &&
             cc[8] == 'A' && cc[10] == 'A' && cc[12] == 'C' )
        {
          infile.CloseFile();
          mprintf("DEBUG:\tFound G R O M A C\n");
          return true;
        }
      }
      ++cc;
    }
    ptr = infile.NextLine();
  }
  infile.CloseFile();
  return false;
}