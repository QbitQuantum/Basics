// Look for 'key' as an environment variable named COMPlus_<key>. The returned value
// is nullptr if it is not found, or a string if found. If not nullptr, the returned
// value must be freed with jitInstance.freeLongLivedArray(value).
wchar_t* GetCOMPlusVariable(const wchar_t* key, JitInstance& jitInstance)
{
    static const wchar_t Prefix[]  = W("COMPlus_");
    static const size_t  PrefixLen = (sizeof(Prefix) / sizeof(Prefix[0])) - 1;

    // Prepend "COMPlus_" to the provided key
    size_t   keyLen       = wcslen(key);
    size_t   keyBufferLen = keyLen + PrefixLen + 1;
    wchar_t* keyBuffer =
        reinterpret_cast<wchar_t*>(jitInstance.allocateArray(static_cast<ULONG>(sizeof(wchar_t) * keyBufferLen)));
    wcscpy_s(keyBuffer, keyBufferLen, Prefix);
    wcscpy_s(&keyBuffer[PrefixLen], keyLen + 1, key);

    // Look up the environment variable
    DWORD valueLen = GetEnvironmentVariableW(keyBuffer, nullptr, 0);
    if (valueLen == 0)
    {
        jitInstance.freeArray(keyBuffer);
        return nullptr;
    }

    // Note this value must live as long as the jit instance does.
    wchar_t* value       = reinterpret_cast<wchar_t*>(jitInstance.allocateLongLivedArray(sizeof(wchar_t) * valueLen));
    DWORD    newValueLen = GetEnvironmentVariableW(keyBuffer, value, valueLen);

    jitInstance.freeArray(keyBuffer);
    if (valueLen < newValueLen)
    {
        jitInstance.freeLongLivedArray(value);
        return nullptr;
    }

    return value;
}