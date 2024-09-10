void
NLSHandler::printBeginOfDataLine()
{
    char szNumb[20];

#if defined(XALAN_STRICT_ANSI_HEADERS)
    using std::sprintf;
#endif

    sprintf(
        szNumb,
        "%d ^",
        m_runningNumber);

    ++m_runningNumber;

    if (m_createUnicode)
    {
        m_stream.write(
            szNumb,
            XMLString::stringLen(szNumb));
    }
    else
    {
        m_stream.writeAsASCII(
            szNumb,
            XMLString::stringLen(szNumb));
    }
}