bool Tokenizer::InitFromBuffer(const wxString& buffer, const wxString& fileOfBuffer, size_t initLineNumber)
{
    BaseInit();
    m_BufferLen = buffer.Length();
    m_Buffer = buffer + _T(" "); // + 1 => sentinel
    m_IsOK = true;
    m_Filename = fileOfBuffer;
    m_LineNumber = initLineNumber;
    return true;
}