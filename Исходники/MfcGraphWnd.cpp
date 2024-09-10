void MfcViewAdapter::regenAll(bool changed)
{
    if (changed) {
        _coreView->submitBackDoc(this, changed);
    }
    _coreView->submitDynamicShapes(this);

    _canvas.clearCachedBitmap();
    if (_wnd->GetSafeHwnd()) {
        _wnd->InvalidateRect(NULL, FALSE);
    }
}