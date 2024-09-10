EFI_STATUS
DevicePathConsistMappingSort (
  IN  EFI_DEVICE_PATH_PROTOCOL **DevicePathBuffer,
  IN  UINTN                    DevicePathNum
  )
{
  QSort (DevicePathBuffer, DevicePathNum, sizeof (EFI_DEVICE_PATH_PROTOCOL *), DevicePathConsistMappingCompare);
  return EFI_SUCCESS;
}