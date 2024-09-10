int doDumpHeapInstance(const char *BinaryFilename) {
  PipeMemoryReader Pipe = createPipeMemoryReader();

  pid_t pid = _fork();
  switch (pid) {
    case -1:
      errorAndExit("Couldn't fork child process");
      exit(EXIT_FAILURE);
    case 0: { // Child:
      close(PipeMemoryReader_getParentWriteFD(&Pipe));
      close(PipeMemoryReader_getParentReadFD(&Pipe));
      dup2(PipeMemoryReader_getChildReadFD(&Pipe), STDIN_FILENO);
      dup2(PipeMemoryReader_getChildWriteFD(&Pipe), STDOUT_FILENO);
      _execv(BinaryFilename, NULL);
      exit(EXIT_SUCCESS);
    }
    default: { // Parent
      close(PipeMemoryReader_getChildReadFD(&Pipe));
      close(PipeMemoryReader_getChildWriteFD(&Pipe));
      SwiftReflectionContextRef RC = swift_reflection_createReflectionContext(
        (void*)&Pipe,
        PipeMemoryReader_getPointerSize,
        PipeMemoryReader_getSizeSize,
        PipeMemoryReader_readBytes,
        PipeMemoryReader_getStringLength,
        PipeMemoryReader_getSymbolAddress);

      uint8_t PointerSize = PipeMemoryReader_getPointerSize((void*)&Pipe);
      if (PointerSize != sizeof(uintptr_t))
        errorAndExit("Child process had unexpected architecture");

      PipeMemoryReader_receiveReflectionInfo(RC, &Pipe);

      while (1) {
        InstanceKind Kind = PipeMemoryReader_receiveInstanceKind(&Pipe);
        switch (Kind) {
        case Object:
          printf("Reflecting an object.\n");
          if (!reflectHeapObject(RC, Pipe))
            return EXIT_SUCCESS;
          break;
        case Existential: {
          swift_typeref_t AnyTR
            = swift_reflection_typeRefForMangledTypeName(RC, "_TtP_", 5);

          printf("Reflecting an existential.\n");
          if (!reflectExistential(RC, Pipe, AnyTR))
            return EXIT_SUCCESS;
          break;
        }
        case ErrorExistential: {
          swift_typeref_t ErrorTR
            = swift_reflection_typeRefForMangledTypeName(RC,
              "_TtPs5Error_", 21);
          printf("Reflecting an error existential.\n");
          if (!reflectExistential(RC, Pipe, ErrorTR))
            return EXIT_SUCCESS;
          break;
        }
        case Closure:
          printf("Reflecting a closure.\n");
          if (!reflectHeapObject(RC, Pipe))
            return EXIT_SUCCESS;
          break;
        case None:
          swift_reflection_destroyReflectionContext(RC);
          printf("Done.\n");
          return EXIT_SUCCESS;
        }
      }
    }
  }
  return EXIT_SUCCESS;
}