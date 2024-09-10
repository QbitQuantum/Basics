  /// Load the combined index from disk, then load every file referenced by
  /// the index and add them to the generator, then performs the promotion and
  /// cross module importing on the files mentioned on the command line
  /// (these must match the index content).
  void import() {
    if (InputFilenames.size() != 1 && !OutputFilename.empty())
      report_fatal_error("Can't handle a single output filename and multiple "
                         "input files, do not provide an output filename and "
                         "the output files will be suffixed from the input "
                         "ones.");

    auto Index = loadCombinedIndex();
    auto InputBuffers = loadAllFilesForIndex(*Index);
    for (auto &MemBuffer : InputBuffers)
      ThinGenerator.addModule(MemBuffer->getBufferIdentifier(),
                              MemBuffer->getBuffer());

    for (auto &Filename : InputFilenames) {
      LLVMContext Ctx;
      auto TheModule = loadModule(Filename, Ctx);

      ThinGenerator.crossModuleImport(*TheModule, *Index);

      std::string OutputName = OutputFilename;
      if (OutputName.empty()) {
        OutputName = Filename + ".thinlto.imported.bc";
      }
      writeModuleToFile(*TheModule, OutputName);
    }
  }