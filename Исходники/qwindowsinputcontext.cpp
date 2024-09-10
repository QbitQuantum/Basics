void QWindowsInputContext::cursorRectChanged()
{
    if (!m_compositionContext.hwnd)
        return;
    const QInputMethod *inputMethod = qApp->inputMethod();
    QRect cursorRectangle = inputMethod->cursorRectangle().toRect();
    if (!cursorRectangle.isValid())
        return;

    if (QWindowsContext::verboseInputMethods)
        qDebug() << __FUNCTION__<< cursorRectangle;

    const HIMC himc = ImmGetContext(m_compositionContext.hwnd);
    if (!himc)
        return;
    // Move candidate list window to the microfocus position.
    COMPOSITIONFORM cf;
    // ### need X-like inputStyle config settings
    cf.dwStyle = CFS_FORCE_POSITION;
    cf.ptCurrentPos.x = cursorRectangle.x();
    cf.ptCurrentPos.y = cursorRectangle.y();

    CANDIDATEFORM candf;
    candf.dwIndex = 0;
    candf.dwStyle = CFS_EXCLUDE;
    candf.ptCurrentPos.x = cursorRectangle.x();
    candf.ptCurrentPos.y = cursorRectangle.y() + cursorRectangle.height();
    candf.rcArea.left = cursorRectangle.x();
    candf.rcArea.top = cursorRectangle.y();
    candf.rcArea.right = cursorRectangle.x() + cursorRectangle.width();
    candf.rcArea.bottom = cursorRectangle.y() + cursorRectangle.height();

    if (m_compositionContext.haveCaret)
        SetCaretPos(cursorRectangle.x(), cursorRectangle.y());

    ImmSetCompositionWindow(himc, &cf);
    ImmSetCandidateWindow(himc, &candf);
    ImmReleaseContext(m_compositionContext.hwnd, himc);
}