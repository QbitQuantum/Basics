/**
 * @brief isSyntheticLCtrl
 * @param   pMsg  Windows WM_[SYS]KEY* event message structure
 * @return  true if this is a synthetic LCtrl event, false otherwise
 * This function is a heuristic to tell whether a key event is the first in
 * a synthetic LCtrl+RAlt sequence which Windows uses to signal AltGr.  Our
 * heuristic is in two parts.  First of all, we check whether there is a pending
 * RAlt key event matching this LCtrl event (i.e. both key up or both key down)
 * and if there is, we check whether the current layout has an AltGr key.  We
 * check this by looking to see if any of the layout-dependent keys has a symbol
 * associated when AltGr is pressed.
 */
static bool isSyntheticLCtrl(MSG *pMsg)
{
    MSG peekMsg;
    /** Keyboard state array with VK_CONTROL and VK_MENU depressed. */
    const BYTE auKeyStates[256] =
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x80, 0x80 };
    WORD ach;
    unsigned i;

    Assert(   pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN
           || pMsg->message == WM_KEYUP || pMsg->message == WM_SYSKEYUP);
    if (   ((RT_HIWORD(pMsg->lParam) & 0xFF) != 0x1d /* scan code: Control */)
        || RT_HIWORD(pMsg->lParam) & KF_EXTENDED)
        return false;
    if (!PeekMessage(&peekMsg, NULL, WM_KEYFIRST, WM_KEYLAST, PM_NOREMOVE))
        return false;
    if (   (pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN)
        && (peekMsg.message != WM_KEYDOWN && peekMsg.message != WM_SYSKEYDOWN))
        return false;
    if (   (pMsg->message == WM_KEYUP || pMsg->message == WM_SYSKEYUP)
        && (peekMsg.message != WM_KEYUP && peekMsg.message != WM_SYSKEYUP))
        return false;
    if (   ((RT_HIWORD(peekMsg.lParam) & 0xFF) != 0x38 /* scan code: Alt */)
        || !(RT_HIWORD(peekMsg.lParam) & KF_EXTENDED))
        return false;
    /* If we got this far then we have a key event which could potentially
     * be a synthetic left control.  Now we check to see whether the current
     * keyboard layout actually has an AltGr key by checking whether any of
     * the keys which might do produce a symbol when AltGr (Control + Alt) is
     * depressed.  Generally this loop will exit pretty early (it exits on the
     * first iteration for my German layout).  If there is no AltGr key in the
     * layout then it will run right through, but that should not happen very
     * often as we should hardly ever reach the loop in that case.
     *
     * In theory we could do this once and cache the result, but that involves
     * tracking layout switches to invalidate the cache, and I don't think
     * that the added complexity is worth the price.
     */
    for (i = '0'; i <= VK_OEM_102; ++i)
    {
        if (ToAscii(i, 0, auKeyStates, &ach, 0))
            break;
        /* Skip ranges of virtual keys which are undefined or not relevant. */
        if (i == '9')
            i = 'A' - 1;
        if (i == 'Z')
            i = VK_OEM_1 - 1;
        if (i == VK_OEM_3)
            i = VK_OEM_4 - 1;
        if (i == VK_OEM_8)
            i = VK_OEM_102 - 1;
    }
    if (i > VK_OEM_102)
        return false;
    return true;
}