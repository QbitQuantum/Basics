 inline std::wstring datetime_cast<std::wstring, CalendarDatetime, const wchar_t*>(const CalendarDatetime& dt, const wchar_t* const& format)
 {
     const auto wdt = datetime_cast<win::CalendarDatetime>(dt);
     std::wstring sdt{ format };
     wchar_t datetimeBuffer[128] = {};
     if (GetDateFormatEx(LOCALE_NAME_INVARIANT, 0, &wdt, sdt.c_str(), datetimeBuffer, _countof(datetimeBuffer), nullptr) > 0)
         sdt = datetimeBuffer;
     if (GetTimeFormatEx(LOCALE_NAME_INVARIANT, 0, &wdt, sdt.c_str(), datetimeBuffer, _countof(datetimeBuffer)) > 0)
         sdt = datetimeBuffer;
     return sdt;
 }