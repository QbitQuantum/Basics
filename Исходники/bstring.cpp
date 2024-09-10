BString::BString(const UString& s)
{
    if (s.isNull())
        m_bstr = 0;
    else
        m_bstr = SysAllocStringLen(s.characters(), s.length());
}