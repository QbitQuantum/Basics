void VlrCompressor::compress(const char *inbuf)
{
    // First time through.
    if (!m_encoder || !m_compressor)
    {
        // Get the position, which is 0 since we
        // are just starting to write
        m_chunkInfoPos = m_stream.m_buf.size();

        // Seek over the chunk info offset value
        unsigned char skip[sizeof(uint64_t)] = {0};
        m_stream.putBytes(skip, sizeof(skip));
        m_chunkOffset = m_chunkInfoPos + sizeof(uint64_t);

        resetCompressor();
    }
    else if (m_chunkPointsWritten == m_chunksize)
    {
        resetCompressor();
        newChunk();
    }
    m_compressor->compress(inbuf);
    m_chunkPointsWritten++;
}