bool SDFfile::ID_SDF(CpptrajFile& fileIn) {
  // NOTE: ASSUMES FILE IS ALREADY SETUP!
  if (fileIn.OpenFile()) return false;
  // Search for V2000 somewhere in line 4
  const char* ptr = 0;
  for (int i = 0; i < 4; i++)
    if ( (ptr = fileIn.NextLine()) == 0 ) {
      fileIn.CloseFile();
      return false;
    }
  fileIn.CloseFile();
  std::string line( ptr ); // Line 4, Connection table
  if ( line.find( "V2000" ) != std::string::npos ) return true;
  return false;
}