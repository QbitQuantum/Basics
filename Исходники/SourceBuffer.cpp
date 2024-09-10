void
SourceBuffer::AppendBuffer(const ArrayBuffer& aData, ErrorResult& aRv)
{
  MOZ_ASSERT(NS_IsMainThread());
  MSE_API("AppendBuffer(ArrayBuffer)");
  aData.ComputeLengthAndData();
  AppendData(aData.Data(), aData.Length(), aRv);
}