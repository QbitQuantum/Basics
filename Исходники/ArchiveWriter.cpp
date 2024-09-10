// Write one member out to the file.
bool
Archive::writeMember(
  const ArchiveMember& member,
  std::ofstream& ARFile,
  bool CreateSymbolTable,
  bool TruncateNames,
  bool ShouldCompress,
  std::string* ErrMsg
) {

  unsigned filepos = ARFile.tellp();
  filepos -= 8;

  // Get the data and its size either from the
  // member's in-memory data or directly from the file.
  size_t fSize = member.getSize();
  const char *data = (const char*)member.getData();
  MemoryBuffer *mFile = 0;
  if (!data) {
    mFile = MemoryBuffer::getFile(member.getPath().c_str(), ErrMsg);
    if (mFile == 0)
      return true;
    data = mFile->getBufferStart();
    fSize = mFile->getBufferSize();
  }

  // Now that we have the data in memory, update the
  // symbol table if its a bitcode file.
  if (CreateSymbolTable && member.isBitcode()) {
    std::vector<std::string> symbols;
    std::string FullMemberName = archPath.str() + "(" + member.getPath().str()
      + ")";
    Module* M = 
      GetBitcodeSymbols((const unsigned char*)data,fSize,
                        FullMemberName, Context, symbols, ErrMsg);

    // If the bitcode parsed successfully
    if ( M ) {
      for (std::vector<std::string>::iterator SI = symbols.begin(),
           SE = symbols.end(); SI != SE; ++SI) {

        std::pair<SymTabType::iterator,bool> Res =
          symTab.insert(std::make_pair(*SI,filepos));

        if (Res.second) {
          symTabSize += SI->length() +
                        numVbrBytes(SI->length()) +
                        numVbrBytes(filepos);
        }
      }
      // We don't need this module any more.
      delete M;
    } else {
      delete mFile;
      if (ErrMsg)
        *ErrMsg = "Can't parse bitcode member: " + member.getPath().str()
          + ": " + *ErrMsg;
      return true;
    }
  }

  int hdrSize = fSize;

  // Compute the fields of the header
  ArchiveMemberHeader Hdr;
  bool writeLongName = fillHeader(member,Hdr,hdrSize,TruncateNames);

  // Write header to archive file
  ARFile.write((char*)&Hdr, sizeof(Hdr));

  // Write the long filename if its long
  if (writeLongName) {
    ARFile.write(member.getPath().str().data(),
                 member.getPath().str().length());
  }

  // Write the (possibly compressed) member's content to the file.
  ARFile.write(data,fSize);

  // Make sure the member is an even length
  if ((ARFile.tellp() & 1) == 1)
    ARFile << ARFILE_PAD;

  // Close the mapped file if it was opened
  delete mFile;
  return false;
}