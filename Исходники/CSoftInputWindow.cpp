void CSoftInputWindow::InitDockWindow()
{
    AutoPtr<IWindow> window;
    GetWindow((IWindow**)&window);
    AutoPtr<IWindowManagerLayoutParams> lp;
    window->GetAttributes((IWindowManagerLayoutParams**)&lp);
    lp->SetType(mWindowType);

    AutoPtr<ICharSequence> name;
    CString::New(mName, (ICharSequence**)&name);
    lp->SetTitle(name);

    lp->SetGravity(mGravity);
    UpdateWidthHeight(lp);

    window->SetAttributes(lp);

    Int32 windowSetFlags = IWindowManagerLayoutParams::FLAG_LAYOUT_IN_SCREEN;
    Int32 windowModFlags = IWindowManagerLayoutParams::FLAG_LAYOUT_IN_SCREEN |
            IWindowManagerLayoutParams::FLAG_NOT_FOCUSABLE |
            IWindowManagerLayoutParams::FLAG_DIM_BEHIND;

    if (!mTakesFocus) {
        windowSetFlags |= IWindowManagerLayoutParams::FLAG_NOT_FOCUSABLE;
    } else {
        windowSetFlags |= IWindowManagerLayoutParams::FLAG_NOT_TOUCH_MODAL;
        windowModFlags |= IWindowManagerLayoutParams::FLAG_NOT_TOUCH_MODAL;
    }

    window->SetFlags(windowSetFlags, windowModFlags);
}