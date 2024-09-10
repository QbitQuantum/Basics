/*
 * @implemented
 */
int CHString::CompareNoCase(LPCWSTR lpsz) const
{
    // Just call the deprecated function here - no matter we are null terminated
    // Did you read my statement about how safe is this implementation?
    return wcsicmp(m_pchData, lpsz);
}