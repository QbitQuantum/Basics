int
wmain(int argc, wchar_t** argv)
{
  if (argc != 3) {
    printf("Usage: redit <exe file> <icon file>\n");
    return 1;
  }

  mozilla::ScopedClose file;
  if (0 != _wsopen_s(&file.rwget(),
                     argv[2],
                     _O_BINARY | _O_RDONLY,
                     _SH_DENYWR,
                     _S_IREAD)
  || (-1 == file)) {
    fprintf(stderr, "Unable to open icon file.\n");
    return 1;
  }

  // Load all the data from the icon file
  long filesize = _filelength(file);
  nsAutoArrayPtr<BYTE> data(new BYTE[filesize]);
  if(!data) {
    fprintf(stderr, "Failed to allocate memory for icon file.\n");
    return 1;
  }
  _read(file, data, filesize);

  IconHeader* header = reinterpret_cast<IconHeader*>(data.get());

  // Open the target library for updating
  ScopedResourceUpdate updateRes(BeginUpdateResourceW(argv[1], FALSE));
  if (NULL == updateRes) {
    fprintf(stderr, "Unable to open library for modification.\n");
    return 1;
  }

  // Allocate the group resource entry
  long groupSize = sizeof(IconHeader)
                 + header->ImageCount * sizeof(IconResEntry);
  nsAutoArrayPtr<BYTE> group(new BYTE[groupSize]);
  if(!group) {
    fprintf(stderr, "Failed to allocate memory for new images.\n");
    return 1;
  }
  memcpy(group, data, sizeof(IconHeader));

  IconDirEntry* sourceIcon =
                    reinterpret_cast<IconDirEntry*>(data
                                                  + sizeof(IconHeader));
  IconResEntry* targetIcon =
                    reinterpret_cast<IconResEntry*>(group
                                                  + sizeof(IconHeader));

  for (int id = 1; id <= header->ImageCount; id++) {
    // Add the individual icon
    if (!UpdateResourceW(updateRes, RT_ICON, MAKEINTRESOURCE(id),
                         MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
                         data + sourceIcon->ImageOffset,
                         sourceIcon->ImageSize)) {
      fprintf(stderr, "Unable to update resource (RT_ICON).\n");
      return 1;
    }
    // Copy the data for this icon
    // (note that the structs have different sizes)
    memcpy(targetIcon, sourceIcon, sizeof(IconResEntry));
    targetIcon->ResourceID = id;
    sourceIcon++;
    targetIcon++;
  }

  if (!UpdateResourceW(updateRes, RT_GROUP_ICON, L"MAINICON",
                       MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
                       group, groupSize)) {
    fprintf(stderr, "Unable to update resource (RT_GROUP_ICON).\n");
    return 1;
  }

  // Save the modifications
  if(!EndUpdateResourceW(updateRes.forget(), FALSE)) {
    fprintf(stderr, "Unable to write changes to library.\n");
    return 1;
  }

  return 0;
}