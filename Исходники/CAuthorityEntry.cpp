ECode CAuthorityEntry::constructor(
    /* [in] */ const String& host,
    /* [in] */ const String& port)
{
    mOrigHost = host;
    mWild = host.GetLength() > 0 && host.GetChar(0) == '*';
    mHost = mWild ? host.Substring(1)/*.intern()*/ : host;
    mPort = !port.IsNull() ? port.ToInt32() : -1;
    return NOERROR;
}