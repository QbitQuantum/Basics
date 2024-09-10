HashResult BCryptHashImpl::Calculate(const Aws::String& str)
{
    if(!IsValid())
    {
        return HashResult();
    }

    std::lock_guard<std::mutex> locker(m_algorithmMutex);

    BCryptHashContext context(m_algorithmHandle, m_hashObject, m_hashObjectLength);
    if (!context.IsValid())
    {
        AWS_LOG_ERROR(BCRYPT_LOG_TAG, "Error creating hash handle.");
        return HashResult();
    }

    return HashData(context, (PBYTE)str.c_str(), static_cast<ULONG>(str.length()));
}