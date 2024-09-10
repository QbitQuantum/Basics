static NET_LUID getLuid(const char* name, struct Except* eh)
{
    uint16_t ifName[IF_MAX_STRING_SIZE + 1] = {0};
    WinFail_check(eh,
        (!MultiByteToWideChar(CP_UTF8, 0, name, strlen(name), ifName, IF_MAX_STRING_SIZE + 1))
    );
    NET_LUID out;
    WinFail_check(eh, ConvertInterfaceAliasToLuid(ifName, &out));
    return out;
}