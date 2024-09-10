String CHttpAuthHeader::TrimDoubleQuotesIfAny(
    /* [in] */ const String& value)
{
    if (value != NULL) {
        Int32 len = value.GetLength();
        if (len > 2
                && value.GetChar(0) == '\"'
                && value.GetChar(len -1) == '\"') {
            return value.Substring(1, len - 1);
        }
    }

    return value;
}