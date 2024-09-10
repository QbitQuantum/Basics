// Look up multiple symbols in the symbol table and return a set of
// ModuleProviders that define those symbols.
bool
Archive::findModulesDefiningSymbols(std::set<std::string>& symbols,
                                    std::set<ModuleProvider*>& result,
                                    std::string* error) {
  if (!mapfile || !base) {
    if (error)
      *error = "Empty archive invalid for finding modules defining symbols";
    return false;
  }

  if (symTab.empty()) {
    // We don't have a symbol table, so we must build it now but lets also
    // make sure that we populate the modules table as we do this to ensure
    // that we don't load them twice when findModuleDefiningSymbol is called
    // below.

    // Get a pointer to the first file
    const char* At  = base + firstFileOffset;
    const char* End = mapfile->getBufferEnd();

    while ( At < End) {
      // Compute the offset to be put in the symbol table
      unsigned offset = At - base - firstFileOffset;

      // Parse the file's header
      ArchiveMember* mbr = parseMemberHeader(At, End, error);
      if (!mbr)
        return false;

      // If it contains symbols
      if (mbr->isBitcode()) {
        // Get the symbols
        std::vector<std::string> symbols;
        std::string FullMemberName = archPath.toString() + "(" +
          mbr->getPath().toString() + ")";
        ModuleProvider* MP = 
          GetBitcodeSymbols((const unsigned char*)At, mbr->getSize(),
                            FullMemberName, symbols, error);

        if (MP) {
          // Insert the module's symbols into the symbol table
          for (std::vector<std::string>::iterator I = symbols.begin(),
               E=symbols.end(); I != E; ++I ) {
            symTab.insert(std::make_pair(*I, offset));
          }
          // Insert the ModuleProvider and the ArchiveMember into the table of
          // modules.
          modules.insert(std::make_pair(offset, std::make_pair(MP, mbr)));
        } else {
          if (error)
            *error = "Can't parse bitcode member: " + 
              mbr->getPath().toString() + ": " + *error;
          delete mbr;
          return false;
        }
      }

      // Go to the next file location
      At += mbr->getSize();
      if ((intptr_t(At) & 1) == 1)
        At++;
    }
  }

  // At this point we have a valid symbol table (one way or another) so we
  // just use it to quickly find the symbols requested.

  for (std::set<std::string>::iterator I=symbols.begin(),
       E=symbols.end(); I != E;) {
    // See if this symbol exists
    ModuleProvider* mp = findModuleDefiningSymbol(*I,error);
    if (mp) {
      // The symbol exists, insert the ModuleProvider into our result,
      // duplicates wil be ignored
      result.insert(mp);

      // Remove the symbol now that its been resolved, being careful to
      // post-increment the iterator.
      symbols.erase(I++);
    } else {
      ++I;
    }
  }
  return true;
}