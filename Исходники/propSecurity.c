/*
* propSecurityConstructor
*
* Purpose:
*
* Initialize class object, query type info, Vtbl, AccessTable, object specific methods.
*
*/
HRESULT propSecurityConstructor(
    _In_ IObjectSecurity *This,
    _In_ PROP_OBJECT_INFO *Context,
    _In_ POPENOBJECTMETHOD OpenObjectMethod,
    _In_opt_ PCLOSEOBJECTMETHOD CloseObjectMethod,
    _In_ ULONG psiFlags
)
{
    BOOL                        cond = FALSE;
    ULONG                       bytesNeeded = 0L;
    NTSTATUS                    status;
    SIZE_T                      Size;
    HRESULT                     hResult;
    HANDLE                      hObject = NULL;
    SI_ACCESS                  *TypeAccessTable = NULL;
    POBJECT_TYPE_INFORMATION    TypeInfo = NULL;

    do {
        This->OpenObjectMethod = OpenObjectMethod;

        //if no close method specified, use default
        if (CloseObjectMethod == NULL) {
            This->CloseObjectMethod = propDefaultCloseObject;
        }
        else {
            This->CloseObjectMethod = CloseObjectMethod;
        }

        if (!This->OpenObjectMethod(Context, &hObject, READ_CONTROL)) {
            hResult = E_ACCESSDENIED;
            break;
        }

        bytesNeeded = 0;
        status = NtQueryObject(hObject, ObjectTypeInformation, NULL, 0, &bytesNeeded);
        if (bytesNeeded == 0) {
            hResult = HRESULT_FROM_WIN32(RtlNtStatusToDosError(status));
            break;
        }

        TypeInfo = supHeapAlloc(bytesNeeded);
        if (TypeInfo == NULL) {
            hResult = HRESULT_FROM_WIN32(GetLastError());
            break;
        }

        status = NtQueryObject(hObject, ObjectTypeInformation, TypeInfo,
            bytesNeeded, &bytesNeeded);
        if (!NT_SUCCESS(status)) {
            hResult = HRESULT_FROM_WIN32(RtlNtStatusToDosError(status));
            break;
        }

        This->GenericMapping = TypeInfo->GenericMapping;
        This->ValidAccessMask = TypeInfo->ValidAccessMask;

        supHeapFree(TypeInfo);
        TypeInfo = NULL;

        This->lpVtbl = &g_Vtbl;
        This->ObjectContext = Context;
        This->hInstance = g_WinObj.hInstance;
        This->psiFlags = psiFlags;

        TypeAccessTable = propGetAccessTable(This);

        //allocate access table
        Size = (MAX_KNOWN_GENERAL_ACCESS_VALUE + This->dwAccessMax) * sizeof(SI_ACCESS);
        This->AccessTable = supHeapAlloc(Size);
        if (This->AccessTable == NULL) {
            hResult = HRESULT_FROM_WIN32(GetLastError());
            break;
        }

        //copy object specific access table if it present
        if (TypeAccessTable && This->dwAccessMax) {
            supCopyMemory(This->AccessTable,
                Size,
                TypeAccessTable,
                (This->dwAccessMax * sizeof(SI_ACCESS))
            );
        }

        if (This->ValidAccessMask & DELETE) {
            supCopyMemory(&This->AccessTable[This->dwAccessMax++], sizeof(SI_ACCESS),
                &GeneralAccessValues[0], sizeof(SI_ACCESS));
        }
        if (This->ValidAccessMask & READ_CONTROL) {
            supCopyMemory(&This->AccessTable[This->dwAccessMax++], sizeof(SI_ACCESS),
                &GeneralAccessValues[1], sizeof(SI_ACCESS));
        }
        if (This->ValidAccessMask & WRITE_DAC) {
            supCopyMemory(&This->AccessTable[This->dwAccessMax++], sizeof(SI_ACCESS),
                &GeneralAccessValues[2], sizeof(SI_ACCESS));
        }
        if (This->ValidAccessMask & WRITE_OWNER) {
            supCopyMemory(&This->AccessTable[This->dwAccessMax++], sizeof(SI_ACCESS),
                &GeneralAccessValues[3], sizeof(SI_ACCESS));
        }
        if (This->ValidAccessMask & SYNCHRONIZE) {
            supCopyMemory(&This->AccessTable[This->dwAccessMax++], sizeof(SI_ACCESS),
                &GeneralAccessValues[4], sizeof(SI_ACCESS));
        }
        hResult = S_OK;

    } while (cond);

    //cleanup
    This->CloseObjectMethod(This, hObject);
    if (TypeInfo) {
        supHeapFree(TypeInfo);
    }
    return hResult;
}