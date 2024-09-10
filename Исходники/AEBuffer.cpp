void CAEBuffer::ReAlloc(const size_t size)
{
#if defined(TARGET_WINDOWS)
    m_buffer = (uint8_t*)_aligned_realloc(m_buffer, size, 16);
#else
    uint8_t* tmp = (uint8_t*)_aligned_malloc(size, 16);
    if (m_buffer)
    {
        size_t copy = std::min(size, m_bufferSize);
        memcpy(tmp, m_buffer, copy);
        _aligned_free(m_buffer);
    }
    m_buffer = tmp;
#endif

    m_bufferSize = size;
    m_bufferPos  = std::min(m_bufferPos, m_bufferSize);
}