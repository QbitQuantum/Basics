static DWORD NtOpenObject(OBJECT_TYPE type, PHANDLE phandle, DWORD access, LPCWSTR path)
{
    UNICODE_STRING ustr;

    RtlInitUnicodeString(&ustr, path);

    OBJECT_ATTRIBUTES open_struct = { sizeof(OBJECT_ATTRIBUTES), 0x00, &ustr, 0x40 };

    if (type != FILE_OBJECT)
        access |= STANDARD_RIGHTS_READ;

    IO_STATUS_BLOCK ioStatusBlock;

    switch (type)
    {
    case DIRECTORY_OBJECT:      return NtOpenDirectoryObject(phandle, access, &open_struct);
    case SYMBOLICLINK_OBJECT:   return NtOpenSymbolicLinkObject(phandle, access, &open_struct);
    case MUTANT_OBJECT:         return NtOpenMutant(phandle, access, &open_struct);
    case SECTION_OBJECT:        return NtOpenSection(phandle, access, &open_struct);
    case EVENT_OBJECT:          return NtOpenEvent(phandle, access, &open_struct);
    case SEMAPHORE_OBJECT:      return NtOpenSemaphore(phandle, access, &open_struct);
    case TIMER_OBJECT:          return NtOpenTimer(phandle, access, &open_struct);
    case KEY_OBJECT:            return NtOpenKey(phandle, access, &open_struct);
    case EVENTPAIR_OBJECT:      return NtOpenEventPair(phandle, access, &open_struct);
    case IOCOMPLETION_OBJECT:   return NtOpenIoCompletion(phandle, access, &open_struct);
    case FILE_OBJECT:           return NtOpenFile(phandle, access, &open_struct, &ioStatusBlock, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, 0);
    default:
        return ERROR_INVALID_FUNCTION;
    }
}