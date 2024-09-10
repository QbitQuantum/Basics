/// <summary>
/// Helper function to retrieve the local current time
/// </summary>
inline PWCHAR GetLocalCurrentTime(PWCHAR buffer, UINT length)
{
    __time64_t currentTime = _time64(nullptr);
    tm localTime;
    _localtime64_s(&localTime, &currentTime);

    wcsftime(buffer, length, L"%#I:%M %p", &localTime);

    return buffer;
}