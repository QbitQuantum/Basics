// Returns the well defined text representation of this expression.
FdoString* FdoInt64Value::ToString()
{
    static const FdoInt32    iBufLen = 256;
    wchar_t szBuf[iBufLen];

    FdoStringUtility::ClearString(m_toString);

    if (IsNull())
    {
        m_toString = FdoStringUtility::MakeString(FdoStringUtility::NullString);
        return m_toString;
    }

#ifdef _WIN32
    _i64tow(GetInt64(), szBuf, 10);
#else
	swprintf(szBuf, sizeof(szBuf)/sizeof(wchar_t), L"%lld", GetInt64());
#endif
    m_toString = FdoStringUtility::MakeString(szBuf);
    return m_toString;
}