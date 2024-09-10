bool TestRecognizeMappingText(_In_ PMAPPING_SERVICE_INFO mappingServiceInfo, _In_z_ const wchar_t* queryValue, _In_z_ const wchar_t* expectedValue)
{
    MAPPING_PROPERTY_BAG mappingPropertyBag;
    ZeroMemory(&mappingPropertyBag, sizeof(mappingPropertyBag));
    mappingPropertyBag.Size = sizeof(mappingPropertyBag);
    bool succeeded = false;

    size_t queryValueLength = wcslen(queryValue);
    if (SUCCEEDED(MappingRecognizeText(mappingServiceInfo, queryValue, static_cast<DWORD>(queryValueLength + 1), 0, NULL, &mappingPropertyBag)))
    {
        if (mappingPropertyBag.dwRangesCount > 0)
        {
            const wchar_t* actualValue = static_cast<const wchar_t*>(mappingPropertyBag.prgResultRanges[0].pData);
            succeeded = 0 == wcscmp(expectedValue, actualValue);
        }
        MappingFreePropertyBag(&mappingPropertyBag);
    }

    return succeeded;
}