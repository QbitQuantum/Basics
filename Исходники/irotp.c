HRESULT __cdecl IrotRevoke(
    IrotHandle h,
    IrotCookie cookie,
    IrotContextHandle *ctxt_handle,
    PInterfaceData *obj,
    PInterfaceData *mk)
{
    struct rot_entry *rot_entry;

    WINE_TRACE("%d\n", cookie);

    EnterCriticalSection(&csRunningObjectTable);
    LIST_FOR_EACH_ENTRY(rot_entry, &RunningObjectTable, struct rot_entry, entry)
    {
        if (rot_entry->cookie == cookie)
        {
            HRESULT hr = S_OK;

            list_remove(&rot_entry->entry);
            LeaveCriticalSection(&csRunningObjectTable);

            *obj = MIDL_user_allocate(FIELD_OFFSET(InterfaceData, abData[rot_entry->object->ulCntData]));
            *mk = MIDL_user_allocate(FIELD_OFFSET(InterfaceData, abData[rot_entry->moniker->ulCntData]));
            if (*obj && *mk)
            {
                (*obj)->ulCntData = rot_entry->object->ulCntData;
                memcpy((*obj)->abData, rot_entry->object->abData, (*obj)->ulCntData);
                (*mk)->ulCntData = rot_entry->moniker->ulCntData;
                memcpy((*mk)->abData, rot_entry->moniker->abData, (*mk)->ulCntData);
            }
            else
            {
                MIDL_user_free(*obj);
                MIDL_user_free(*mk);
                hr = E_OUTOFMEMORY;
            }

            rot_entry_release(rot_entry);
            *ctxt_handle = NULL;
            return hr;
        }
    }
    LeaveCriticalSection(&csRunningObjectTable);

    return E_INVALIDARG;
}