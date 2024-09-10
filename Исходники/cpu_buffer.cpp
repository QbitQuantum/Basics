uint32_t CPUBuffer::GetCurrentElementNumber() const
{
  uint32_t pointerDiff = static_cast<uint32_t>(GetCursor() - Data());
  ASSERT(pointerDiff % GetElementSize() == 0, ());
  return pointerDiff / GetElementSize();
}