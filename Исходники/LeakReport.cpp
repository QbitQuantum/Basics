LeakReport::UrlRecord *
LeakReport::LogUrl(char16 const * url, void * globalObject)
{
    UrlRecord * record = NoCheckHeapNewStruct(UrlRecord);

    size_t length = wcslen(url) + 1; // Add 1 for the NULL.
    char16* urlCopy = NoCheckHeapNewArray(char16, length);
    js_memcpy_s(urlCopy, (length - 1) * sizeof(char16), url, (length - 1) * sizeof(char16));
    urlCopy[length - 1] = _u('\0');

    record->url = urlCopy;
#if _MSC_VER
    record->time = _time64(NULL);
#else
    record->time = time(NULL);
#endif
    record->tid = ::GetCurrentThreadId();
    record->next = nullptr;
    record->scriptEngine = nullptr;
    record->globalObject = globalObject;

    AutoCriticalSection autocs(&s_cs);
    if (LeakReport::urlRecordHead == nullptr)
    {
        Assert(LeakReport::urlRecordTail == nullptr);
        LeakReport::urlRecordHead = record;
        LeakReport::urlRecordTail = record;
    }
    else
    {
        LeakReport::urlRecordTail->next = record;
        LeakReport::urlRecordTail = record;
    }

    return record;
}