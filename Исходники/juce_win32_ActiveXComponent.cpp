bool ActiveXControlComponent::createControl (const void* controlIID)
{
    deleteControl();
    ComponentPeer* const peer = getPeer();

    // the component must have already been added to a real window when you call this!
    jassert (dynamic_cast <Win32ComponentPeer*> (peer) != nullptr);

    if (dynamic_cast <Win32ComponentPeer*> (peer) != nullptr)
    {
        const Point<int> pos (getTopLevelComponent()->getLocalPoint (this, Point<int>()));
        HWND hwnd = (HWND) peer->getNativeHandle();

        ScopedPointer<Pimpl> newControl (new Pimpl (hwnd, *this));

        HRESULT hr;
        if ((hr = OleCreate (*(const IID*) controlIID, IID_IOleObject, 1 /*OLERENDER_DRAW*/, 0,
                             newControl->clientSite, newControl->storage,
                             (void**) &(newControl->control))) == S_OK)
        {
            newControl->control->SetHostNames (L"Juce", 0);

            if (OleSetContainedObject (newControl->control, TRUE) == S_OK)
            {
                RECT rect;
                rect.left = pos.getX();
                rect.top = pos.getY();
                rect.right = pos.getX() + getWidth();
                rect.bottom = pos.getY() + getHeight();

                if (newControl->control->DoVerb (OLEIVERB_SHOW, 0, newControl->clientSite, 0, hwnd, &rect) == S_OK)
                {
                    control = newControl;
                    setControlBounds (Rectangle<int> (pos.getX(), pos.getY(), getWidth(), getHeight()));

                    control->controlHWND = ActiveXHelpers::getHWND (this);

                    if (control->controlHWND != 0)
                    {
                        originalWndProc = (void*) (pointer_sized_int) GetWindowLongPtr ((HWND) control->controlHWND, GWLP_WNDPROC);
                        SetWindowLongPtr ((HWND) control->controlHWND, GWLP_WNDPROC, (LONG_PTR) Pimpl::activeXHookWndProc);
                    }

                    return true;
                }
            }
        }
    }

    return false;
}