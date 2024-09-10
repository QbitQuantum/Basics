void Q_mswin::init(WId wid)
{
    _windowId = wid;
    _taskbarMessageId = RegisterWindowMessageW(L"TaskbarButtonCreated");
}