int fchmod(int fd, mode_t mode) {
  HANDLE h = (HANDLE)_get_osfhandle(fd);
  if (h == INVALID_HANDLE_VALUE) {
    return -1;
  }

  FILE_ATTRIBUTE_TAG_INFO attr{};
  if (!GetFileInformationByHandleEx(
          h, FileAttributeTagInfo, &attr, sizeof(attr))) {
    return -1;
  }

  if (mode & _S_IWRITE) {
    attr.FileAttributes &= ~FILE_ATTRIBUTE_READONLY;
  } else {
    attr.FileAttributes |= FILE_ATTRIBUTE_READONLY;
  }

  if (!SetFileInformationByHandle(
          h, FileAttributeTagInfo, &attr, sizeof(attr))) {
    return -1;
  }

  return 0;
}