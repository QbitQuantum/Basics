int main(int argc, char** argv)
{
  if (argc != 2) {
    fprintf(stderr, "usage: fileid <file>\n");
    return 1;
  }

  HANDLE file = CreateFileA(argv[1],
                            GENERIC_READ,
                            FILE_SHARE_READ,
                            nullptr,
                            OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL,
                            nullptr);
  if (file == INVALID_HANDLE_VALUE) {
    fprintf(stderr, "Couldn't open file: %s\n", argv[1]);
    return 1;
  }

  HANDLE mapFile = CreateFileMappingA(file, NULL, PAGE_READONLY, 0, 0, 0);
  if (mapFile == nullptr) {
    fprintf(stderr, "Couldn't create file mapping\n");
    CloseHandle(file);
    return 1;
  }

  uint8_t* base = reinterpret_cast<uint8_t*>(MapViewOfFile(mapFile,
                                                           FILE_MAP_READ,
                                                           0,
                                                           0,
                                                           0));
  if (base == nullptr) {
    fprintf(stderr, "Couldn't map file\n");
    CloseHandle(mapFile);
    CloseHandle(file);
    return 1;
  }

  DWORD size;
  PIMAGE_DEBUG_DIRECTORY debug_dir =
    reinterpret_cast<PIMAGE_DEBUG_DIRECTORY>(
      ImageDirectoryEntryToDataEx(base,
                                  FALSE,
                                  IMAGE_DIRECTORY_ENTRY_DEBUG,
                                  &size,
                                  nullptr));

  bool found = false;
  if (debug_dir->Type == IMAGE_DEBUG_TYPE_CODEVIEW) {
    CV_INFO_PDB70* cv =
      reinterpret_cast<CV_INFO_PDB70*>(base + debug_dir->PointerToRawData);
    if (cv->CvSignature == CV_SIGNATURE_RSDS) {
      found = true;
      print_guid(cv->Signature, cv->Age);
    }
  }

  UnmapViewOfFile(base);
  CloseHandle(mapFile);
  CloseHandle(file);

  return found ? 0 : 1;
}