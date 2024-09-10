bool CAutoConnector::IsConnected()
{
    return ((_attached_hwnd != NULL) && IsWindow(_attached_hwnd));
}