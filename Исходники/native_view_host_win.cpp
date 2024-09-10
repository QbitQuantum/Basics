    IAccessible* NativeViewHostWin::GetNativeViewAccessible()
    {
        HWND hwnd = host_->native_view();
        if(!IsWindow(hwnd))
        {
            return NULL;
        }

        LRESULT ret = SendMessage(hwnd, WM_GETOBJECT, 0, OBJID_CLIENT);
        IAccessible* accessible = NULL;
        HRESULT success = ObjectFromLresult(ret, IID_IDispatch, 0,
            reinterpret_cast<void**>(accessible));
        if(success == S_OK)
        {
            return accessible;
        }
        else
        {
            return NULL;
        }
    }