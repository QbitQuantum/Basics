bool QClipboard::ownsMode(Mode mode) const
{
    if (mode == Clipboard) {
        QClipboardData *d = clipboardData();
#if !defined(Q_OS_WINCE)
        return d->iData && OleIsCurrentClipboard(d->iData) == S_OK;
#else
        return d->iData && GetClipboardOwner() == d->clipBoardViewer->internalWinId();
#endif
    } else {
        return false;
    }
}