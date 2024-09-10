// Save the SA to disc
void SampledSuffixArray::writeSSA(std::string filename)
{
    std::ostream* pWriter = createWriter(filename, std::ios::out | std::ios::binary);
    
    // Write a magic number
    SSA_WRITE(SSA_MAGIC_NUMBER)

    // Write sample rate
    SSA_WRITE(m_sampleRate)

    // Write number of lexicographic index entries
    size_t n = m_saLexoIndex.size();
    SSA_WRITE(n)

    // Write lexo index
    SSA_WRITE_N(m_saLexoIndex.front(), sizeof(SSA_INT_TYPE) * n)
    
    // Write number of samples
    n = m_saSamples.size();
    SSA_WRITE(n)

    // Write samples
    SSA_WRITE_N(m_saSamples.front(), sizeof(SAElem) * n)

    delete pWriter;
}