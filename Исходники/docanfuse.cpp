static NTSTATUS DOKAN_CALLBACK
GetVolumeInformation(LPWSTR VolumeNameBuffer, DWORD VolumeNameSize,
                     LPDWORD VolumeSerialNumber, LPDWORD MaximumComponentLength,
                     LPDWORD FileSystemFlags, LPWSTR FileSystemNameBuffer,
                     DWORD FileSystemNameSize, PDOKAN_FILE_INFO DokanFileInfo) {
  impl_fuse_context *impl = the_impl;
  if (impl->debug())
    FWPRINTF(stderr, L"GetVolumeInformation\n");

  impl_chain_guard guard(impl, DokanFileInfo->ProcessId);
  *VolumeSerialNumber = 0;
  *MaximumComponentLength = 255;
  return errno_to_ntstatus_error(impl->get_volume_information(
      VolumeNameBuffer, VolumeNameSize, FileSystemNameBuffer,
      FileSystemNameSize, DokanFileInfo, FileSystemFlags));
}