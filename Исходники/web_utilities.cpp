plaintext_string win32_encryption::decrypt() const
{
    // Copy the buffer and decrypt to avoid having to re-encrypt.
    auto data = plaintext_string(new std::wstring(reinterpret_cast<const std::wstring::value_type *>(m_buffer.data()), m_buffer.size() / 2));
    if (!CryptUnprotectMemory(
        const_cast<std::wstring::value_type *>(data->c_str()),
        static_cast<DWORD>(m_buffer.size()),
        CRYPTPROTECTMEMORY_SAME_PROCESS))
    {
        throw ::utility::details::create_system_error(GetLastError());
    }
    data->resize(m_numCharacters);
    return std::move(data);
}