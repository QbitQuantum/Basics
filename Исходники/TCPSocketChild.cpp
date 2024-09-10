nsresult
TCPSocketChild::SendSend(const ArrayBuffer& aData,
                         uint32_t aByteOffset,
                         uint32_t aByteLength,
                         uint32_t aTrackingNumber)
{
  uint32_t buflen = aData.Length();
  uint32_t offset = std::min(buflen, aByteOffset);
  uint32_t nbytes = std::min(buflen - aByteOffset, aByteLength);
  FallibleTArray<uint8_t> fallibleArr;
  if (!fallibleArr.InsertElementsAt(0, aData.Data() + offset, nbytes, fallible)) {
    return NS_ERROR_OUT_OF_MEMORY;
  }

  InfallibleTArray<uint8_t> arr;
  arr.SwapElements(fallibleArr);
  SendData(arr, aTrackingNumber);
  return NS_OK;
}