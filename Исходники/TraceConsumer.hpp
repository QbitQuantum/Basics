bool GetEventData(EVENT_RECORD* pEventRecord, wchar_t const* name, T* out, bool bPrintOnError = true)
{
    PROPERTY_DATA_DESCRIPTOR descriptor;
    descriptor.PropertyName = (ULONGLONG) name;
    descriptor.ArrayIndex = ULONG_MAX;

    auto status = TdhGetProperty(pEventRecord, 0, nullptr, 1, &descriptor, sizeof(T), (BYTE*) out);
    if (status != ERROR_SUCCESS) {
        if (bPrintOnError) {
            fprintf(stderr, "error: could not get event %ls property (error=%lu).\n", name, status);
            PrintEventInformation(stderr, pEventRecord);
        }
        return false;
    }

    return true;
}