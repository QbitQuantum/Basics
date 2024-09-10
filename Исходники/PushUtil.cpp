/* static */ bool
PushUtil::CopyArrayBufferToArray(const ArrayBuffer& aBuffer,
                                 nsTArray<uint8_t>& aArray)
{
  aBuffer.ComputeLengthAndData();
  return aArray.SetLength(aBuffer.Length(), fallible) &&
         aArray.ReplaceElementsAt(0, aBuffer.Length(), aBuffer.Data(),
                                  aBuffer.Length(), fallible);
}