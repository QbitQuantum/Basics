QWinEventFilter::QWinEventFilter() :
    tbButtonCreatedMsgId(RegisterWindowMessageW(L"TaskbarButtonCreated"))
{
}