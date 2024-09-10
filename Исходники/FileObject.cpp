NTSTATUS
FileObjectContext::Create()
{
    TRACE_FUNCTION_ENTRY(LEVEL_VERBOSE);
    NTSTATUS status;

    UNICODE_STRING* fileObjectName = WdfFileObjectGetFileName(_FileObject);
    if (CSTR_EQUAL == CompareStringOrdinal(fileObjectName->Buffer, fileObjectName->Length / sizeof(WCHAR), L"\\" FILE_NAMESPACE_NCI_SIMULATOR, int(wcslen(L"\\" FILE_NAMESPACE_NCI_SIMULATOR)), /*IgnoreCase*/ TRUE))
    {
        _Type = Type::NciSim;
    }
    else
    {
        status = STATUS_OBJECT_NAME_NOT_FOUND;
        TRACE_LINE(LEVEL_ERROR, "Unknown file namespace: %S. %!STATUS!", fileObjectName->Buffer, status);
        return status;
    }

    status = _DeviceContext->ClientConnected(this);
    if (!NT_SUCCESS(status))
    {
        TRACE_LINE(LEVEL_ERROR, "DeviceContext::ClientConnected failed. %!STATUS!", status);
        return status;
    }

    TRACE_FUNCTION_SUCCESS(LEVEL_VERBOSE);
    return STATUS_SUCCESS;
}