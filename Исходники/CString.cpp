void CString::copyBufferIfNeeded()
{
    if (!m_buffer || m_buffer->hasOneRef())
        return;

    RefPtr<CStringBuffer> buffer = WTFMove(m_buffer);
    size_t length = buffer->length();
    m_buffer = CStringBuffer::createUninitialized(length);
    memcpy(m_buffer->mutableData(), buffer->data(), length + 1);
}