static void find_reg_tz_info(RTL_TIME_ZONE_INFORMATION *tzi)
{
    static const WCHAR Time_ZonesW[] = { 'M','a','c','h','i','n','e','\\',
        'S','o','f','t','w','a','r','e','\\',
        'M','i','c','r','o','s','o','f','t','\\',
        'W','i','n','d','o','w','s',' ','N','T','\\',
        'C','u','r','r','e','n','t','V','e','r','s','i','o','n','\\',
        'T','i','m','e',' ','Z','o','n','e','s',0 };
    HANDLE hkey;
    ULONG idx;
    OBJECT_ATTRIBUTES attr;
    UNICODE_STRING nameW;
    WCHAR buf[128];

    attr.Length = sizeof(attr);
    attr.RootDirectory = 0;
    attr.ObjectName = &nameW;
    attr.Attributes = 0;
    attr.SecurityDescriptor = NULL;
    attr.SecurityQualityOfService = NULL;
    RtlInitUnicodeString(&nameW, Time_ZonesW);
    if (NtOpenKey(&hkey, KEY_READ, &attr))
    {
        WARN("Unable to open the time zones key\n");
        return;
    }

    idx = 0;
    nameW.Buffer = buf;
    nameW.Length = sizeof(buf);
    nameW.MaximumLength = sizeof(buf);

    while (!RtlpNtEnumerateSubKey(hkey, &nameW, idx++))
    {
        static const WCHAR stdW[] = { 'S','t','d',0 };
        static const WCHAR dltW[] = { 'D','l','t',0 };
        static const WCHAR tziW[] = { 'T','Z','I',0 };
        RTL_TIME_ZONE_INFORMATION reg_tzi;
        HANDLE hSubkey;
        struct tz_reg_data
        {
            LONG bias;
            LONG std_bias;
            LONG dlt_bias;
            RTL_SYSTEM_TIME std_date;
            RTL_SYSTEM_TIME dlt_date;
        } tz_data;

        attr.Length = sizeof(attr);
        attr.RootDirectory = hkey;
        attr.ObjectName = &nameW;
        attr.Attributes = 0;
        attr.SecurityDescriptor = NULL;
        attr.SecurityQualityOfService = NULL;
        if (NtOpenKey(&hSubkey, KEY_READ, &attr))
        {
            WARN("Unable to open subkey %s\n", debugstr_wn(nameW.Buffer, nameW.Length/sizeof(WCHAR)));
            continue;
        }

#define get_value(hkey, name, type, data, len) \
    if (!reg_query_value(hkey, name, type, data, len)) \
    { \
        WARN("can't read data from %s\n", debugstr_w(name)); \
        NtClose(hkey); \
        continue; \
    }

        get_value(hSubkey, stdW, REG_SZ, reg_tzi.StandardName, sizeof(reg_tzi.StandardName));
        get_value(hSubkey, dltW, REG_SZ, reg_tzi.DaylightName, sizeof(reg_tzi.DaylightName));
        get_value(hSubkey, tziW, REG_BINARY, &tz_data, sizeof(tz_data));

#undef get_value

        reg_tzi.Bias = tz_data.bias;
        reg_tzi.StandardBias = tz_data.std_bias;
        reg_tzi.DaylightBias = tz_data.dlt_bias;
        reg_tzi.StandardDate = tz_data.std_date;
        reg_tzi.DaylightDate = tz_data.dlt_date;

        TRACE("%s: bias %d\n", debugstr_wn(nameW.Buffer, nameW.Length/sizeof(WCHAR)), reg_tzi.Bias);
        TRACE("std (d/m/y): %u/%02u/%04u day of week %u %u:%02u:%02u.%03u bias %d\n",
            reg_tzi.StandardDate.wDay, reg_tzi.StandardDate.wMonth,
            reg_tzi.StandardDate.wYear, reg_tzi.StandardDate.wDayOfWeek,
            reg_tzi.StandardDate.wHour, reg_tzi.StandardDate.wMinute,
            reg_tzi.StandardDate.wSecond, reg_tzi.StandardDate.wMilliseconds,
            reg_tzi.StandardBias);
        TRACE("dst (d/m/y): %u/%02u/%04u day of week %u %u:%02u:%02u.%03u bias %d\n",
            reg_tzi.DaylightDate.wDay, reg_tzi.DaylightDate.wMonth,
            reg_tzi.DaylightDate.wYear, reg_tzi.DaylightDate.wDayOfWeek,
            reg_tzi.DaylightDate.wHour, reg_tzi.DaylightDate.wMinute,
            reg_tzi.DaylightDate.wSecond, reg_tzi.DaylightDate.wMilliseconds,
            reg_tzi.DaylightBias);

        NtClose(hSubkey);

        if (match_tz_info(tzi, &reg_tzi))
        {
            *tzi = reg_tzi;
            NtClose(hkey);
            return;
        }

        /* reset len */
        nameW.Length = sizeof(buf);
        nameW.MaximumLength = sizeof(buf);
    }

    NtClose(hkey);

    FIXME("Can't find matching timezone information in the registry for "
          "bias %d, std (d/m/y): %u/%02u/%04u, dlt (d/m/y): %u/%02u/%04u\n",
          tzi->Bias,
          tzi->StandardDate.wDay, tzi->StandardDate.wMonth, tzi->StandardDate.wYear,
          tzi->DaylightDate.wDay, tzi->DaylightDate.wMonth, tzi->DaylightDate.wYear);
}