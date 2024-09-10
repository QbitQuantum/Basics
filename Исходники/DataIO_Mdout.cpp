// DataIO_Mdout::ID_DataFormat()
bool DataIO_Mdout::ID_DataFormat(CpptrajFile& infile) {
  if (infile.OpenFile()) return false;
  bool isMdout = false;
  std::string line = infile.GetLine();
  if (line[0] == '\n') {
    line = infile.GetLine();
    if (line.compare(0, 15, "          -----") == 0) {
      line = infile.GetLine();
      if (line.compare(0, 15, "          Amber") == 0)
        isMdout = true;
    }
  }
  infile.CloseFile();
  return isMdout;
}