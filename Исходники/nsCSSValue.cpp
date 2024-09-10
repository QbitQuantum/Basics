// static
already_AddRefed<nsStringBuffer>
nsCSSValue::BufferFromString(const nsString& aValue)
{
  nsStringBuffer* buffer = nsStringBuffer::FromString(aValue);
  if (buffer) {
    buffer->AddRef();
    return buffer;
  }
  
  PRUnichar length = aValue.Length();

  // NOTE: Alloc prouduces a new, already-addref'd (refcnt = 1) buffer.
  buffer = nsStringBuffer::Alloc((length + 1) * sizeof(PRUnichar));
  if (NS_LIKELY(buffer != 0)) {
    PRUnichar* data = static_cast<PRUnichar*>(buffer->Data());
    nsCharTraits<PRUnichar>::copy(data, aValue.get(), length);
    // Null-terminate.
    data[length] = 0;
  }

  return buffer;
}