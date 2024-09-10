String FormData::decode(const CString& data) const
{
    return encoding().decode(data.data(), data.length());
}