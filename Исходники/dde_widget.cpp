bool DDEWidget::ddeExecute(MSG* message, long* result)
// ----------------------------------------------------------------------------
//   Process a Windows WM_DDE_EXECUTE message
// ----------------------------------------------------------------------------
{
    // unpack the DDE message
    UINT_PTR unused;
    HGLOBAL hData;
    bool ok;
    //IA64: Assume DDE LPARAMs are still 32-bit
    ok = (::UnpackDDElParam(WM_DDE_EXECUTE, message->lParam, &unused,
                            (UINT_PTR*)&hData) != 0);
    XL_ASSERT(ok);
    if (!ok)
        return false;

    QString command = QString::fromWCharArray((LPCWSTR)::GlobalLock(hData));
    ::GlobalUnlock(hData);

    // acknowledge now - before attempting to execute
    ::PostMessage((HWND)message->wParam, WM_DDE_ACK, (WPARAM)winId(),
                  //IA64: Assume DDE LPARAMs are still 32-bit
                  ReuseDDElParam(message->lParam, WM_DDE_EXECUTE, WM_DDE_ACK,
                                 (UINT)0x8000, (UINT_PTR)hData));

    // don't execute the command when the window is disabled
    if (!isEnabled())
    {
        *result = 0;
        return true;
    }

    QRegExp regCommand("^\\[(\\w+)\\((.*)\\)\\]$");
    if(regCommand.exactMatch(command))
    {
        executeDdeCommand(regCommand.cap(1), regCommand.cap(2));
    }

    *result = 0;
    return true;
}