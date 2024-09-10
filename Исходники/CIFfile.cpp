/** Determine if fileIn is a CIF file. Look for entries beginning with 
  * an underscore (indicating data block), and a 'loop_' keyword or
  * '_entry.id' block.
  */
bool CIFfile::ID_CIF(CpptrajFile& fileIn) {
  // NOTE: ASSUME FILE SET UP FOR READ
  if (fileIn.OpenFile()) return false;
  int ndata = 0; // Number of '_XXX' entries seen
  bool foundLoop = false;
  bool foundEntryID = false;
  for (int i = 0; i < 10; i++) {
    std::string lineIn = fileIn.GetLine();
    if (lineIn[0] == '_') ndata++;
    if (lineIn.compare(0,5,"loop_")==0) foundLoop = true;
    if (lineIn.compare(0,9,"_entry.id")==0) foundEntryID = true;
  }
  fileIn.CloseFile();
  return ( ndata > 2 && (foundLoop || foundEntryID) );
}