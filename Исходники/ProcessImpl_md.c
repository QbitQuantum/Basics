static BOOL hasInheritFlag(HANDLE handle)
{
    DWORD mask;
    if (GetHandleInformation(handle, &mask)) {
        return mask & HANDLE_FLAG_INHERIT;
    }
    return FALSE;
}