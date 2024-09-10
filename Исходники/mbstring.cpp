__cdecl
_mbsninc(
         const unsigned char *string, size_t count)
{
    unsigned char *ret;
    CPINFO cpinfo;

    PERF_ENTRY(_mbsninc);
    ENTRY("_mbsninc (string=%p, count=%lu)\n", string, count);
    if (string == NULL)
    {
        ret = NULL;
    }
    else
    {
        ret = (unsigned char *) string;
        if (GetCPInfo(CP_ACP, &cpinfo) && cpinfo.MaxCharSize == 1)
        {
            ret += std::min(count, strlen((const char*)string));
        }
        else
        {
            while (count-- && (*ret != 0))
            {
                if (IsDBCSLeadByteEx(CP_ACP, *ret))
                {
                    ++ret;
                }
                ++ret;
            }
        }
    }
    LOGEXIT("_mbsninc returning unsigned char* %p (%s)\n", ret, ret);
    PERF_EXIT(_mbsninc);
    return ret;
}