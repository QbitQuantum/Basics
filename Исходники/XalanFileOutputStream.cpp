void
XalanFileOutputStream::writeData(
            const char*     theBuffer,
            size_type       theBufferLength)
{
#if defined(XALAN_WINDOWS)
    DWORD           theBytesWritten;

    assert(size_t(DWORD(theBufferLength)) == theBufferLength);

    if (WriteFile(m_handle, theBuffer, DWORD(theBufferLength), &theBytesWritten, 0) == false ||
        theBytesWritten != theBufferLength)
    {
        XalanDOMString  theExceptionBuffer(getMemoryManager());

        throw XalanFileOutputStreamWriteException(
                m_fileName,
                GetLastError(),
                theExceptionBuffer);
    }
#else
#if defined(XALAN_STRICT_ANSI_HEADERS)
    using std::fwrite;
#endif

    const size_t    theBytesWritten =
        fwrite(theBuffer,
               1,
               theBufferLength,
               m_handle);

    if (theBytesWritten != theBufferLength)
    {
       XalanDOMString   theExceptionBuffer(getMemoryManager());

        throw XalanFileOutputStreamWriteException(
                m_fileName,
                errno,
                theExceptionBuffer);
    }
#endif
}