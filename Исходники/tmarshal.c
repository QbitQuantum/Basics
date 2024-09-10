static DWORD CALLBACK host_object_proc(LPVOID p)
{
    struct host_object_data *data = p;
    HRESULT hr;
    MSG msg;

    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    if (data->filter)
    {
        IMessageFilter * prev_filter = NULL;
        hr = CoRegisterMessageFilter(data->filter, &prev_filter);
        if (prev_filter) IMessageFilter_Release(prev_filter);
        ok_ole_success(hr, CoRegisterMessageFilter);
    }

    hr = CoMarshalInterface(data->stream, &data->iid, data->object, MSHCTX_INPROC, NULL, data->marshal_flags);
    ok_ole_success(hr, CoMarshalInterface);

    /* force the message queue to be created before signaling parent thread */
    PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

    SetEvent(data->marshal_event);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (msg.hwnd == NULL && msg.message == RELEASEMARSHALDATA)
        {
            trace("releasing marshal data\n");
            CoReleaseMarshalData(data->stream);
            SetEvent((HANDLE)msg.lParam);
        }
        else
            DispatchMessage(&msg);
    }

    HeapFree(GetProcessHeap(), 0, data);

    CoUninitialize();

    return hr;
}