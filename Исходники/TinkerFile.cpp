bool TinkerFile::ID_Tinker(CpptrajFile& fileIn) {
  // NOTE: ASSUME FILE SET UP FOR READ
  if (fileIn.OpenFile()) return false;
  ArgList firstLine( fileIn.NextLine() );
  ArgList secondLine( fileIn.NextLine() );
  ArgList thirdLine( fileIn.NextLine() );
  fileIn.CloseFile();
  // First line should have <natom> <title> only
  int natom = 0;
  std::string title;
  if ( SetNatomAndTitle(firstLine, natom, title) != 0 )
    return false;
  //mprinterr("Past SetNatomAndTitle\n");
  if (secondLine.Nargs() == 6) {
    bool isBoxLine = true;
    for (int i = 0; i < 6; i++) {
      // It is a box line if all 6 tokens are doubles
      try {
        convertToDouble( secondLine.GetStringNext() );
      } 
      catch (std::runtime_error e) {
        if (i != 1) return false;
        // We found a non-double on the second character -- it could be an atom
        // name. Check that the rest of the line matches an atom record
        isBoxLine = false;
        break;
      }
    }
    // If we are here it is not a box line, so make sure 
    if (!isBoxLine) {
      return IsAtomLine(secondLine);
    } else { // our second line WAS a box, now check the 3rd line
      return IsAtomLine(thirdLine);
    }
  }
  // There is no box, check that the second line is an atom line
  return IsAtomLine(secondLine);
}