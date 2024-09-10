bool WindowsJob::queryInformation(JOBOBJECTINFOCLASS informationClass,
        LPVOID lpInformation,
        DWORD cbInformationLength,
        LPDWORD lpReturnLength)
{
    return !!QueryInformationJobObject(jobHandle_, informationClass, lpInformation,
        cbInformationLength, lpReturnLength);
}